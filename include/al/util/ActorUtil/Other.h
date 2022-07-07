#pragma once

#include "al/actor/LiveActor.h"

namespace al {

void validateClipping(LiveActor*);
void invalidateClipping(LiveActor*);

void validateCollisionParts(al::LiveActor*);
void invalidateCollisionParts(al::LiveActor*);

} // namespace al