#pragma once

#include "al/actor/LiveActor.h"
#include "al/resource/Resource.h"
#include "al/sensor/HitSensor.h"
#include <sead/math/seadMatrix.h>

namespace al {

class CollisionObj : public al::LiveActor {
public:
    CollisionObj(const ActorInitInfo& info, Resource*, const char* collisionPartsName, HitSensor* collisionSensor, const sead::Matrix34f*, const char*);
};

CollisionObj* createCollisionObj(LiveActor* resourceOwner, const ActorInitInfo& info, const char* collisionPartsName, HitSensor*, const char* collisionFollowJointName, const char* = nullptr);

} // namespace al