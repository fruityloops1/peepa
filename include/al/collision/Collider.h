#pragma once

#include "al/actor/LiveActor.h"
#include "al/collision/CollisionDirector.h"
#include "al/interfaces/IUseCollision.h"
#include "math/seadMatrix.h"
#include "math/seadVector.h"
#include "types.h"

namespace al {

class Collider : IUseCollision {
    CollisionDirector* mCollisionDirector = nullptr;
    u64 unk[2];
    sead::Matrix34f* unk2;
    sead::Vector3f* unk3[2];

public:
    float mRadius;
    float mYOffset;
    u8 unk4[0x248];

};

float getColliderRadius(const LiveActor* actor);
float getColliderOffsetY(const LiveActor* actor);

} // namespace al