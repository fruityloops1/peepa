#pragma once

#include "al/Yaml/ByamlIter.h"
#include <sead/basis/seadTypes.h>

namespace al {

class PlacementInfo {
    ByamlIter mPlacementIter;
    ByamlIter mUnitConfigIter;
    u8 _20[0x10];

public:
    PlacementInfo();

    const ByamlIter& getPlacementIter() const { return mPlacementIter; }
    const ByamlIter& getUnitConfigIter() const { return mUnitConfigIter; }
};

} // namespace al