#pragma once

#include "al/actor/LiveActor.h"

namespace al {

bool isDead(const LiveActor* actor);
bool isClipped(const LiveActor* actor);

void onCollide(LiveActor* actor);
void offCollide(LiveActor* actor);

} // namespace