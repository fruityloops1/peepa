#include "Game/Player/PlayerActor.h"
#include "Game/Scene/SingleModeScene.h"
#include "Game/Scene/StageScene.h"
#include "Game/Sequence/ProductSequence.h"
#include "al/Base/String.h"
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
#include "nn/socket.h"
#include "pe/BunbunMod.h"
#include "pe/DbgGui/DbgGui.h"
#include "pe/EchoEmitterMod.h"
#include "pe/Exception.h"
#include "pe/Factory/ProjectActorFactory.h"
#include "pe/Hacks/PlacementHolderMod.h"
#include "pe/Hacks/WiiUMod.h"
#include "pe/Util/Hooks.h"
#include "pe/Util/Log.h"
#include "program/imgui_nvn.h"
#include "replace.hpp"
#include "util/modules.hpp"
#include "util/sys/rw_pages.hpp"
#include <sead/filedevice/nin/seadNinSDFileDeviceNin.h>
#include <sead/filedevice/seadFileDeviceMgr.h>
#include <sead/heap/seadExpHeap.h>
#include <sead/heap/seadHeapMgr.h>

HOOK_DEFINE_TRAMPOLINE(StageSceneMovementHook) { static void Callback(StageScene*); };
HOOK_DEFINE_TRAMPOLINE(SingleModeSceneInitHook) { static void Callback(SingleModeScene*, const al::SceneInitInfo&); };
HOOK_DEFINE_TRAMPOLINE(SingleModeSceneDtorHook) { static void Callback(SingleModeScene*); };
HOOK_DEFINE_TRAMPOLINE(ProductSequenceInitHook) { static void Callback(ProductSequence*, const al::SequenceInitInfo&); };
void StageSceneMovementHook::Callback(StageScene* scene) { Orig(scene); }
void SingleModeSceneInitHook::Callback(SingleModeScene* scene, const al::SceneInitInfo& info) { Orig(scene, info); }
void SingleModeSceneDtorHook::Callback(SingleModeScene* scene) { }
void productSequenceInitHook(ProductSequence* thisPtr, const al::Nerve* nerve, int nerveStateNum) { thisPtr->initNerve(nerve, nerveStateNum); }
void projectActorFactoryHook(ProjectActorFactory* factory) { new (factory) pe::ProjectActorFactory(); }
void playerActorInitHook(PlayerActor* actor, const al::ActorInitInfo& info) { al::initActorSceneInfo(actor, info); }

void productSequenceUpdateHook(ProductSequence* sequence)
{
    sequence->al::Sequence::update();

    {
        sead::ScopedCurrentHeapSetter heapSetter(pe::gui::getDbgGuiHeap());

        auto* dbgGui = pe::gui::DbgGui::instance();
        if (dbgGui)
            dbgGui->update();
    }
}

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
}

PATCH_DEFINE_ASM(SceneObjHolderSize, "mov w2, #0x3e");

HOOK_DEFINE_TRAMPOLINE(CreateFileDeviceMgr) { static void Callback(sead::FileDeviceMgr * thisPtr); };
void CreateFileDeviceMgr::Callback(sead::FileDeviceMgr* thisPtr)
{
    Orig(thisPtr);
    *(bool*)(uintptr_t(thisPtr) + 81) = nn::fs::MountSdCardForDebug("sd").IsFailure();
}

void drawDbgGui()
{
    sead::ScopedCurrentHeapSetter heapSetter(pe::gui::getDbgGuiHeap());

    auto* dbgGui = pe::gui::DbgGui::instance();
    if (dbgGui)
        dbgGui->draw();
}

extern "C" void exl_main(void* x0, void* x1)
{
    exl::hook::Initialize();

    using Patcher = exl::patch::CodePatcher;
    using namespace exl::patch::inst;

    {
        constexpr size_t poolSize = 0xC0000;
        void* pool = malloc(poolSize);
        nn::socket::Initialize(pool, poolSize, 0x4000, 0xe);
    }

    SceneObjHolderSize::InstallAtOffset(0x003e624c);
    StageSceneMovementHook::InstallAtOffset(0x003f2d20);
    SingleModeSceneInitHook::InstallAtOffset(0x003e7090);
    SingleModeSceneDtorHook::InstallAtOffset(0x003e6810);
    ProductSequenceInitHook::InstallAtOffset(0x003fc4d0);
    CreateFileDeviceMgr::InstallAtOffset(0x0070e7e0);
    Patcher(0x00360198).BranchLinkInst((void*)playerActorInitHook);
    Patcher(0x003fcf68).BranchLinkInst((void*)productSequenceUpdateHook);
    Patcher(0x003d86b0).BranchInst((void*)projectActorFactoryHook);
    Patcher(0x003fcb10).BranchLinkInst((void*)productSequenceInitHook);

    // pe::initUserExceptionHandler();
    pe::initBunbunModHooks();
    pe::initEchoEmitterModHooks();
    pe::initPlacementHolderModHooks();

    // pe::initWiiUModHooks();

    nvnImGui::InstallHooks();
    nvnImGui::addDrawFunc(drawDbgGui);
}

extern "C" NORETURN void exl_exception_entry()
{
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}
