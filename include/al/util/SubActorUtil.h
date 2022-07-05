#pragma once

#include "al/actor/LiveActor.h"

namespace al {

LiveActor* getSubActor(const al::LiveActor*, int index);
LiveActor* getSubActor(const al::LiveActor* actor, const char* subActorName);
LiveActor* tryGetSubActor(const al::LiveActor* actor, const char* subActorName);
int getSubActorNum(const al::LiveActor* actor);

} // namespace al