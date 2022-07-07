#pragma once

#include "al/sensor/SensorMsg.h"

namespace al {

bool isMsgPlayerFloorTouch(const al::SensorMsg*);

bool isMsgTouchAssist(const al::SensorMsg*);

} // namespace al