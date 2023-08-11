#include "pe/Exception.h"
#include "lib/util/modules.hpp"
#include "nn/os.h"
#include "pe/Util/Log.h"
#include <cstdlib>

static void userExceptionHandler(nn::os::UserExceptionInfo* info)
{
    // auto& c = pe::MPClient::instance();
    if (/*c.isConnected()*/ false) {
        auto& rtld = exl::util::GetRtldModuleInfo();
        auto& main = exl::util::GetMainModuleInfo();
        auto& self = exl::util::GetSelfModuleInfo();
        auto& nnsdk = exl::util::GetSdkModuleInfo();

        const struct {
            const exl::util::ModuleInfo& info;
            const char name[8];
        } modules[] { { rtld, "rtld" }, { main, "main" }, { self, "self" }, { nnsdk, "nnsdk" } };

        struct ModuleAddrOffset {
            const char* moduleName;
            uintptr_t offset;
        };

        auto getAddrOffset = [&modules](uintptr_t addr) {
            ModuleAddrOffset offset { "?", 0 };
            for (const auto& module : modules)
                if (addr >= module.info.m_Total.m_Start && addr <= module.info.m_Total.GetEnd()) {
                    offset.moduleName = module.name;
                    offset.offset = addr - module.info.m_Total.m_Start;
                    break;
                }

            return offset;
        };

        pe::log("Modules: ");
        for (auto& module : modules)
            pe::log("\t%s: %.16lx - %.16lx ", module.name, module.info.m_Total.m_Start, module.info.m_Total.GetEnd());

        pe::log("Fault Address: %.16lx ", info->FAR.x);
        pe::log("Registers: ");
        for (int i = 0; i < 29; i++) {
            auto offset = getAddrOffset(info->CpuRegisters[i].x);
            if (offset.offset != 0)
                pe::log("\tX[%02d]: %.16lx (%s + 0x%.8lx) ", i, info->CpuRegisters[i].x, offset.moduleName, offset.offset);
            else
                pe::log("\tX[%02d]: %.16lx ", i, info->CpuRegisters[i].x);
        }

        const struct {
            const char name[3];
            uintptr_t value;
        } registers[] {
            { "FP", info->FP.x },
            { "LR", info->LR.x },
            { "SP", info->SP.x },
            { "PC", info->PC.x },
        };

        for (auto& r : registers) {
            auto offset = getAddrOffset(r.value);
            if (offset.offset != 0)
                pe::log("\t%s:    %.16lx (%s + 0x%.8lx) ", r.name, r.value, offset.moduleName, offset.offset);
            else
                pe::log("\t%s:    %.16lx  ", r.name, r.value);
        }
        pe::log("Stack Trace: ");

        uintptr_t* frame = (uintptr_t*)info->FP.x;
        uintptr_t* prevFrame = nullptr;
        int i = 0;
        while (frame != nullptr and prevFrame != frame) {
            prevFrame = frame;
            auto offset = getAddrOffset(frame[1]);
            if (offset.offset != 0)
                pe::log("\tReturnAddress[%02d]: %.16lx (%s + 0x%.8lx) ", i, frame[1], offset.moduleName, offset.offset);
            else
                pe::log("\tReturnAddress[%02d]: %.16lx ", i, frame[1]);
            frame = (uintptr_t*)frame[0];

            i++;
        }

        // pe::MPClient::instance().disconnect();
    }
}

void pe::initUserExceptionHandler()
{
    constexpr size_t userExceptionHandlerStackSize = 0x1000;
    void* userExceptionHandlerStack = malloc(userExceptionHandlerStackSize);
    nn::os::SetUserExceptionHandler(userExceptionHandler, userExceptionHandlerStack, userExceptionHandlerStackSize, nullptr);
}
