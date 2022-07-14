#pragma once

#include "al/actor/LiveActor.h"
#include "al/sensor/HitSensor.h"

namespace al {

al::HitSensor* getHitSensor(const al::LiveActor* actor, const char* sensorName);
al::LiveActor* getSensorHost(const al::HitSensor* sensor);

} // namespace al