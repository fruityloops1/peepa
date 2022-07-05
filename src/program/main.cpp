#include "al/util/ActorUtil.h"
#include "game/factory/ProjectActorFactory.h"
#include "game/player/PlayerActor.h"
#include "game/scene/SingleModeScene.h"
#include "lib.hpp"
#include "nn/socket.h"
#include "pe/factory/ProjectActorFactory.h"

MAKE_HOOK_T(void, singleModeSceneMovementHook, (SingleModeScene * scene), {
    PlayerActor* player = static_cast<PlayerActor*>(scene->mLiveActorKit->mPlayerHolder->tryGetPlayer(0));
    impl(scene);
});

void projectActorFactoryHook(ProjectActorFactory* factory) { new (factory) pe::ProjectActorFactory(); }

void playerActorInitHook(PlayerActor* actor, const al::ActorInitInfo& info)
{
    al::initActorSceneInfo(actor, info);
}

extern "C" void exl_main(void* x0, void* x1)
{
    envSetOwnProcessHandle(exl::util::proc_handle::Get());
    exl::hook::Initialize();

    constexpr size_t poolSize = 0xC0000;
    void* pool = malloc(poolSize);
    nn::socket::Initialize(pool, poolSize, 0x4000, 0xe);

    INJECT_HOOK_T(0x003e84d0, singleModeSceneMovementHook);
    exl::patch::CodePatcher(0x003d86b0).BranchInst((void*)projectActorFactoryHook);
    exl::patch::CodePatcher(0x00360198).BranchLinkInst((void*)playerActorInitHook);
}

extern "C" NORETURN void exl_exception_entry()
{
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}