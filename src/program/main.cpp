#include "Game/Player/PlayerActor.h"
#include "Game/Scene/SingleModeScene.h"
#include "Game/Scene/StageScene.h"
#include "Game/Sequence/ProductSequence.h"
#include "al/Controller/ControllerUtil.h"
#include "al/LiveActor/LiveActorFunction.h"
#include "al/Memory/MemorySystem.h"
#include "al/Nerve/NerveFunction.h"
#include "al/Sequence/SequenceInitInfo.h"
#include "devenv/seadFontMgr.h"
#include "diag/assert.hpp"
#include "imgui.h"
#include "lib.hpp"
#include "nn/fs.h"
#include "nn/oe.h"
#include "nn/os.h"
#include "pe/BunbunMod.h"
#include "pe/Client/MPClient.h"
#include "pe/DbgGui/DbgGui.h"
#include "pe/EchoEmitterMod.h"
#include "pe/Exception.h"
#include "pe/Factory/ProjectActorFactory.h"
#include "pe/Hacks/PlacementHolderMod.h"
#include "pe/Hacks/WiiUMod.h"
#include "pe/RCSMultiplayer.h"
#include "pe/RCSPlayers.h"
#include "pe/Sequence/ProductStateTest.h"
#include "pe/Util/Hooks.h"
#include "program/imgui_nvn.h"
#include "replace.hpp"
#include "util/modules.hpp"
#include "util/sys/rw_pages.hpp"
#include <sead/filedevice/nin/seadNinSDFileDeviceNin.h>
#include <sead/filedevice/seadFileDeviceMgr.h>
#include <sead/heap/seadExpHeap.h>
#include <sead/heap/seadHeapMgr.h>

constexpr static bool isSingleModeMultiplayer = false;

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

    {
        sead::ScopedCurrentHeapSetter heapSetter(pe::gui::getDbgGuiHeap());

        auto* dbgGui = pe::gui::DbgGui::instance();
        if (dbgGui)
            dbgGui->update();
    }

    // RUN_EACH(300, pe::MPClient::instance().ping(););
}

void productSequenceInitHook(ProductSequence* thisPtr, const al::Nerve* nerve, int nerveStateNum)
{
    thisPtr->initNerve(nerve, nerveStateNum);
}

void projectActorFactoryHook(ProjectActorFactory* factory) { new (factory) pe::ProjectActorFactory(); }

void playerActorInitHook(PlayerActor* actor, const al::ActorInitInfo& info)
{
    if (isSingleModeMultiplayer)
        pe::initPuppets(info);
    al::initActorSceneInfo(actor, info);
}

HOOK_DEFINE_TRAMPOLINE(ProductSequenceInitHook) { static void Callback(ProductSequence*, const al::SequenceInitInfo&); };

static void initDbgGui()
{
    pe::gui::getDbgGuiHeap() = sead::ExpHeap::create(1024 * 1024 * 1, "DbgGuiHeap", al::getSequenceHeap(), 8, sead::ExpHeap::cHeapDirection_Forward, false);
    pe::createPlacementInfoHeap();
    {
        sead::ScopedCurrentHeapSetter heapSetter(pe::gui::getDbgGuiHeap());
        pe::gui::DbgGui::createInstance(nullptr);
    }
}

void ProductSequenceInitHook::Callback(ProductSequence* sequence, const al::SequenceInitInfo& info)
{
    Orig(sequence, info);

    initDbgGui();
    pe::gui::DbgGui::instance()->mSharedData.productSequence = sequence;

    // pe::MPClient::instance().connect(pe::MPClient::sServerIp, 7032);
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

HOOK_DEFINE_TRAMPOLINE(CreateFileDeviceMgr) { static void Callback(sead::FileDeviceMgr * thisPtr); };

struct FileDeviceMgrIsMountedSd {
    typedef bool type;
};

void CreateFileDeviceMgr::Callback(sead::FileDeviceMgr* thisPtr)
{

    Orig(thisPtr);

    // balls
    // thisPtr->mMountedSd = true;
    *(bool*)(uintptr_t(thisPtr) + 81) = nn::fs::MountSdCardForDebug("sd").IsFailure();

    // literally not a thing
    // sead::NinSDFileDevice* sdFileDevice = new sead::NinSDFileDevice();

    // thisPtr->mount(sdFileDevice);
}

void drawDbgGui()
{
    sead::ScopedCurrentHeapSetter heapSetter(pe::gui::getDbgGuiHeap());

    auto* dbgGui = pe::gui::DbgGui::instance();
    if (dbgGui)
        dbgGui->draw();
}

HOOK_DEFINE_TRAMPOLINE(FilePrintHook) { static void Callback(sead::FileDevice * thisPtr, sead::FileHandle * handle, const sead::SafeString& file, sead::FileDevice::FileOpenFlag flag, u32 smth); };

void FilePrintHook::Callback(sead::FileDevice* thisPtr, sead::FileHandle* handle, const sead::SafeString& file, sead::FileDevice::FileOpenFlag flag, u32 smth)
{
    pe::MPClient::instance().log("%s ", file.cstr());
    Orig(thisPtr, handle, file, flag, smth);
}

extern "C" void exl_main(void* x0, void* x1)
{
    exl::hook::Initialize();

    using Patcher = exl::patch::CodePatcher;
    using namespace exl::patch::inst;

    if (isSingleModeMultiplayer or true) {
        constexpr size_t poolSize = 0xC0000;
        void* pool = malloc(poolSize);
        nn::socket::Initialize(pool, poolSize, 0x4000, 0xe);
    }

    SceneObjHolderSize::InstallAtOffset(0x003e624c);
    FixHook::InstallAtOffset(0x008d1598);
    StageSceneMovementHook::InstallAtOffset(0x003f2d20);
    SingleModeSceneInitHook::InstallAtOffset(0x003e7090);
    SingleModeSceneDtorHook::InstallAtOffset(0x003e6810);
    ProductSequenceInitHook::InstallAtOffset(0x003fc4d0);
    CreateFileDeviceMgr::InstallAtOffset(0x0070e7e0);
    Patcher(0x00360198).BranchLinkInst((void*)playerActorInitHook);
    Patcher(0x003fcf68).BranchLinkInst((void*)productSequenceUpdateHook);
    Patcher(0x003d86b0).BranchInst((void*)projectActorFactoryHook);
    // Patcher(0x009b79e0).BranchLinkInst((void*)enableSharcHook);
    Patcher(0x003fcb10).BranchLinkInst((void*)productSequenceInitHook);

    // FilePrintHook::InstallAtOffset(0x0070d100);

    // worldmap shit
    /*Patcher(0x000990c0).BranchLinkInst(reinterpret_cast<void*>(uintptr_t(0x0035fa90) + exl::util::modules::GetTargetStart()));
    Patcher(0x0009910c).BranchLinkInst(reinterpret_cast<void*>(uintptr_t(0x0032d0e0) + exl::util::modules::GetTargetStart()));
    Patcher(0x000990cc).WriteInst(Nop());
    Patcher(0x0008b334).WriteInst(Nop());
    Patcher(0x00099158).WriteInst(Nop());
    Patcher(0x000899d4).WriteInst(Nop());
    Patcher(0x0008df4c).WriteInst(Nop());*/

    if (isSingleModeMultiplayer) {
        pe::RCSPlayers::initHooks();
        pe::initRCSMultiplayerHooks();
        pe::initPuppetHooks();
    }

    // pe::initUserExceptionHandler();
    pe::initBunbunModHooks();
    pe::initEchoEmitterModHooks();
    pe::initPlacementHolderModHooks();
    // pe::initWiiUModHooks();
    // pe::installProductStateTestHooks();
    // installProductSequenceHooks();

    nvnImGui::InstallHooks();
    nvnImGui::addDrawFunc(drawDbgGui);
}

extern "C" NORETURN void exl_exception_entry()
{
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}
