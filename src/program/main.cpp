#include "al/sequence/SequenceInitInfo.h"
#include "al/util/ActorUtil/Init.h"
#include "al/util/StringUtil.h"
#include "game/player/PlayerActor.h"
#include "game/scene/SingleModeScene.h"
#include "game/scene/StageScene.h"
#include "game/sequence/ProductSequence.h"
#include "lib.hpp"
#include "nn/os.h"
#include "pe/BunbunMod.h"
#include "pe/EchoEmitterMod.h"
#include "pe/RCSMultiplayer.h"
#include "pe/RCSPlayers.h"
#include "pe/client/MPClient.h"
#include "pe/factory/ProjectActorFactory.h"
#include "pe/util/Hooks.h"
#include "replace.hpp"
#include "util/modules.hpp"
#include "util/sys/rw_pages.hpp"

constexpr static bool isSingleModeMultiplayer = true;

HOOK_DEFINE_TRAMPOLINE(StageSceneMovementHook) { static void Callback(StageScene*); };
HOOK_DEFINE_TRAMPOLINE(SingleModeSceneInitHook) { static void Callback(SingleModeScene*, const al::SceneInitInfo&); };
HOOK_DEFINE_TRAMPOLINE(SingleModeSceneDtorHook) { static void Callback(SingleModeScene*); };

void StageSceneMovementHook::Callback(StageScene* scene)
{
    Orig(scene);
}

void SingleModeSceneInitHook::Callback(SingleModeScene* scene, const al::SceneInitInfo& info)
{
    Orig(scene, info);
}

void SingleModeSceneDtorHook::Callback(SingleModeScene* scene)
{
    pe::MPClient::instance().disconnect();
}

void productSequenceUpdateHook(ProductSequence* sequence)
{
    sequence->al::Sequence::update();

    RUN_EACH(300, pe::MPClient::instance().ping(););
}

void projectActorFactoryHook(ProjectActorFactory* factory) { new (factory) pe::ProjectActorFactory(); }

void playerActorInitHook(PlayerActor* actor, const al::ActorInitInfo& info)
{
    if (isSingleModeMultiplayer)
        pe::initPuppets(info);
    al::initActorSceneInfo(actor, info);
}

void disableTransparentWallHook(al::LiveActor* actor) { actor->kill(); }

void disableDynamicResolutionHook(al::NerveExecutor* graphics)
{
    static class : public al::Nerve {
        void execute(al::NerveKeeper*) override { }
        void executeOnEnd(al::NerveKeeper*) const override { }
    } dummy;
    graphics->initNerve(&dummy);
}

static void userExceptionHandler(nn::os::UserExceptionInfo* info)
{
    auto& c = pe::MPClient::instance();
    if (c.isConnected()) {
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

        c.log("Modules: ");
        for (auto& module : modules)
            c.log("\t%s: %.16lx - %.16lx ", module.name, module.info.m_Total.m_Start, module.info.m_Total.GetEnd());

        c.log("Fault Address: %.16lx ", info->FAR.x);
        c.log("Registers: ");
        for (int i = 0; i < 29; i++) {
            auto offset = getAddrOffset(info->CpuRegisters[i].x);
            if (offset.offset != 0)
                c.log("\tX[%02d]: %.16lx (%s + 0x%.8lx) ", i, info->CpuRegisters[i].x, offset.moduleName, offset.offset);
            else
                c.log("\tX[%02d]: %.16lx ", i, info->CpuRegisters[i].x);
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
                c.log("\t%s:    %.16lx (%s + 0x%.8lx) ", r.name, r.value, offset.moduleName, offset.offset);
            else
                c.log("\t%s:    %.16lx  ", r.name, r.value);
        }
        c.log("Stack Trace: ");

        uintptr_t* frame = (uintptr_t*)info->FP.x;
        uintptr_t* prevFrame = nullptr;
        int i = 0;
        while (frame != nullptr and prevFrame != frame) {
            prevFrame = frame;
            auto offset = getAddrOffset(frame[1]);
            if (offset.offset != 0)
                c.log("\tReturnAddress[%02d]: %.16lx (%s + 0x%.8lx) ", i, frame[1], offset.moduleName, offset.offset);
            else
                c.log("\tReturnAddress[%02d]: %.16lx ", i, frame[1]);
            frame = (uintptr_t*)frame[0];

            i++;
        }

        pe::MPClient::instance().disconnect();
    }
}

HOOK_DEFINE_TRAMPOLINE(ProductSequenceInitHook) { static void Callback(ProductSequence*, const al::SequenceInitInfo&); };

void ProductSequenceInitHook::Callback(ProductSequence* sequence, const al::SequenceInitInfo& info)
{
    Orig(sequence, info);
}

PATCH_DEFINE_ASM(FixHook, R"(
    nop
    nop
    cmp wzr, wzr
)"); // i forgot what this does

PATCH_DEFINE_ASM(SceneObjHolderSize, "mov w2, #0x3e");

bool enableSharcHook(const char* s1, const char* s2)
{
    return al::isEqualSubString(s1, ".sharc");
}

extern "C" void exl_main(void* x0, void* x1)
{
    envSetOwnProcessHandle(exl::util::proc_handle::Get());
    exl::hook::Initialize();

    using Patcher = exl::patch::CodePatcher;
    using namespace exl::patch::inst;

    if (isSingleModeMultiplayer or true) {
        constexpr size_t poolSize = 0xC0000;
        void* pool = malloc(poolSize);
        nn::socket::Initialize(pool, poolSize, 0x4000, 0xe);
    }

    constexpr size_t userExceptionHandlerStackSize = 0x1000;
    void* userExceptionHandlerStack = malloc(userExceptionHandlerStackSize);
    nn::os::SetUserExceptionHandler(userExceptionHandler, userExceptionHandlerStack, userExceptionHandlerStackSize, nullptr);

    SceneObjHolderSize::InstallAtOffset(0x003e624c);
    FixHook::InstallAtOffset(0x008d1598);
    StageSceneMovementHook::InstallAtOffset(0x003f2d20);
    SingleModeSceneInitHook::InstallAtOffset(0x003e7090);
    SingleModeSceneDtorHook::InstallAtOffset(0x003e6810);
    ProductSequenceInitHook::InstallAtOffset(0x003fc4d0);
    Patcher(0x00360198).BranchLinkInst((void*)playerActorInitHook);
    Patcher(0x003fcf68).BranchLinkInst((void*)productSequenceUpdateHook);
    Patcher(0x003d86b0).BranchInst((void*)projectActorFactoryHook);
    Patcher(0x009b79e0).BranchLinkInst((void*)enableSharcHook);
    // Patcher(0x002d65b4).BranchLinkInst((void*)disableTransparentWallHook);
    // Patcher(0x0080196c).BranchLinkInst((void*)disableDynamicResolutionHook);

    if (isSingleModeMultiplayer) {
        pe::RCSPlayers::initHooks();
        pe::initRCSMultiplayerHooks();
        pe::initPuppetHooks();
    }
    pe::initBunbunModHooks();
    pe::initEchoEmitterModHooks();
}

extern "C" NORETURN void exl_exception_entry()
{
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}