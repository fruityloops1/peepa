#pragma once

#include "al/actor/ActorInitInfo.h"
#include "game/scene/SingleModeScene.h"

namespace pe {

void initPuppets(const al::ActorInitInfo& info);
void initPuppetHooks();
void updatePuppets(SingleModeScene* scene);

enum class PuppetType : u8 {
    RaidonSurf = 0,
    KoopaJr = 1
};

struct PuppetHookState {
    bool isStartAnimHookEnabled = true;
};
PuppetHookState& getPuppetHookState();

} // namespace pe