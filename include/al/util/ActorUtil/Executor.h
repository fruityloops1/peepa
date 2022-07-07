#pragma once

#include "al/actor/LiveActor.h"

namespace al {

void initExecutorMapObj(LiveActor* actor, const ActorInitInfo& info);
void initExecutorEnemyMovement(LiveActor* actor, const ActorInitInfo& info);
void initExecutorPlayerMovement(LiveActor* actor, const ActorInitInfo& info);

} // namespace al