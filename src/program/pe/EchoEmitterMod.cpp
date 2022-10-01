#include "pe/EchoEmitterMod.h"
#include "al/audio/MeInfo.h"
#include "al/interfaces/IUseAudioKeeper.h"
#include "al/scene/SceneInitInfo.h"
#include "al/util/ActorUtil/Flag.h"
#include "al/util/AudioUtil.h"
#include "container/seadPtrArray.h"
#include "game/actors/EchoBlockMapParts.h"
#include "game/scene/StageScene.h"
#include "lib.hpp"
#include "pe/client/MPClient.h"
#include "prim/seadSafeString.h"

HOOK_DEFINE_TRAMPOLINE(EchoBlockMapPartsInitHook) { static void Callback(EchoBlockMapParts*, const al::ActorInitInfo&); };
HOOK_DEFINE_TRAMPOLINE(StageSceneInitHook) { static void Callback(StageScene*, al::SceneInitInfo*); };

static sead::PtrArray<EchoBlockMapParts> allEchoBlocks;

void EchoBlockMapPartsInitHook::Callback(EchoBlockMapParts* actor, const al::ActorInitInfo& info)
{
    Orig(actor, info);
    allEchoBlocks.pushBack(actor);
}

void StageSceneInitHook::Callback(StageScene* scene, al::SceneInitInfo* info)
{
    if (allEchoBlocks.isBufferReady())
        allEchoBlocks.freeBuffer();
    allEchoBlocks.allocBuffer(15, nullptr);
    Orig(scene, info);
}

static void startSeHook(al::IUseAudioKeeper* audioKeeper, const sead::SafeString& seName, al::MeInfo* info)
{
    bool startSound = false;
    for (EchoBlockMapParts& actor : allEchoBlocks)
        if (!al::isClipped(&actor))
            startSound = true;
    if (startSound)
        al::startSe(audioKeeper, seName, info);
}

void pe::initEchoEmitterModHooks()
{
    using Patcher = exl::patch::CodePatcher;

    EchoBlockMapPartsInitHook::InstallAtOffset(0x002278e0);
    StageSceneInitHook::InstallAtOffset(0x003f11d0);
    Patcher(0x002282b8).BranchLinkInst((void*)startSeHook);
}