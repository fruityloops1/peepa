#pragma once

#include "al/HitSensor/HitSensor.h"

namespace al {

class SensorMsg {
};

bool isMsgPlayerFloorTouch(const al::SensorMsg*);
bool isMsgTouchAssist(const al::SensorMsg*);

bool isSensorPlayer(const al::HitSensor*);

} // namespace al