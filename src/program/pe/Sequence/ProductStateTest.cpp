#include "pe/Sequence/ProductStateTest.h"
#include "Game/Scene/LuigiBrosScene.h"
#include "Game/Sequence/ProductSequence.h"
#include "Game/Sequence/ProductStateLuigiBros.h"
#include "al/Memory/MemorySystem.h"
#include "al/Nerve/NerveFunction.h"
#include "al/Nerve/NerveKeeper.h"
#include "al/Sequence/SequenceFunction.h"
#include "patch/code_patcher.hpp"
#include "pe/Client/MPClient.h"
#include <sead/heap/seadHeapMgr.h>

namespace pe {

namespace {
    NERVE_DEF(ProductStateTest, Load)
    NERVE_DEF(ProductStateTest, Wait)
} // namespace

ProductStateTest::ProductStateTest(ProductSequence* host, void* unk1, const al::SequenceInitInfo& info, void* unk2, GameDataHolder* gameDataHolder, StageWipeKeeper* stageWipeKeeper, al::ScreenCaptureExecutor* screenCaptureExecutor)
    : HostStateBase("ProductStateTest", host)
{
    al::initSceneCreator(this, info, gameDataHolder, host->getAudioDirector(), screenCaptureExecutor, nullptr);
}

void ProductStateTest::init()
{
    initNerve(&nrvProductStateTestLoad);
    pe::MPClient::instance().connect(pe::MPClient::sServerIp, 7032);
}

void ProductStateTest::appear()
{
    al::setNerve(this, &nrvProductStateTestLoad);
}

void ProductStateTest::exeLoad()
{
    if (al::isFirstStep(this)) {
        al::createSceneHeap("LuigiBros");
        al::SceneHeapSetter heapSetter;
        LuigiBrosScene* newScene = new LuigiBrosScene;
        mScene = newScene;
        al::setSceneAndUseInitThread(this, newScene, 19, nullptr, -1, "", nullptr);
    }
    if (al::tryEndSceneInitThread(this)) {
        setNerve(this, &nrvProductStateTestWait);
    }
}

void ProductStateTest::exeWait()
{
    if (al::isFirstStep(this)) {
        mScene->appear();
        mHost->setCurrentScene(mScene);
    }
}

PATCH_DEFINE_ASM(ProductSequenceSizeHook, "mov w0, #0x1b8");

static void ctorHook(ProductStateLuigiBros* state, ProductSequence* host, void* unk1, const al::SequenceInitInfo& info, void* unk2, GameDataHolder* gameDataHolder, StageWipeKeeper* stageWipeKeeper, al::ScreenCaptureExecutor* screenCaptureExecutor)
{
    new (state) ProductStateLuigiBros(host, unk1, info, unk2, gameDataHolder, stageWipeKeeper, screenCaptureExecutor);
    host->mStateTest = new pe::ProductStateTest(host, unk1, info, unk2, gameDataHolder, stageWipeKeeper, screenCaptureExecutor);
}

static void initHook(ProductSequence* p, al::NerveStateBase* state, al::Nerve* nrv, const char* name)
{
    al::initNerveState(p, state, nrv, "LuigiBros");
    al::initNerveState(p, p->mStateTest, ProductSequence::getTestNrv(), "Test");
}

void installProductStateTestHooks()
{
    exl::patch::CodePatcher(0x003fcaf4).BranchLinkInst((void*)ctorHook);
    exl::patch::CodePatcher(0x003fcc30).BranchLinkInst((void*)initHook);
    ProductSequenceSizeHook::InstallAtOffset(0x00405010);
}

} // namespace pe
