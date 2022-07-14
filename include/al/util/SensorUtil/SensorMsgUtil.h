#pragma once

#include "al/sensor/HitSensor.h"
#include "al/sensor/SensorMsg.h"

namespace al {

bool isMsgPlayerFloorTouch(const al::SensorMsg*);
bool isMsgTouchAssist(const al::SensorMsg*);

bool isSensorPlayer(const al::HitSensor*);

} // namespace al