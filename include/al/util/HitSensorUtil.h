#pragma once

#include "al/actor/LiveActor.h"
#include "al/sensor/HitSensor.h"

namespace al {

al::HitSensor* getSensor(const al::LiveActor* actor, const char* sensorName);

} // namespace al