#pragma once

#include "al/HitSensor/ScreenPointTarget.h"
#include <sead/container/seadPtrArray.h>

namespace al {

class ScreenPointKeeper {
    sead::PtrArray<ScreenPointTarget> mScreenPointTargets;
};

} // namespace al