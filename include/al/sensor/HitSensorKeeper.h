#pragma once

#include "al/sensor/HitSensor.h"
#include <sead/container/seadPtrArray.h>

namespace al {

    class HitSensorKeeper {
        sead::PtrArray<HitSensor> mHitSensors;
    };

} // namespace al