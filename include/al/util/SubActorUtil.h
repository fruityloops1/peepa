#pragma once

#include "al/actor/LiveActor.h"

namespace al {

void initSubActorKeeperNoFile(LiveActor* actor, const ActorInitInfo& info, int);

LiveActor* getSubActor(const LiveActor*, int index);
LiveActor* getSubActor(const LiveActor* actor, const char* subActorName);
LiveActor* tryGetSubActor(const LiveActor* actor, const char* subActorName);
int getSubActorNum(const LiveActor* actor);

void registerSubActorSyncClipping(LiveActor* parent, LiveActor* sub, u64 = 0);

} // namespace al