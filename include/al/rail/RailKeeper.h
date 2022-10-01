#pragma once

#include "al/byaml/PlacementInfo.h"
#include "al/rail/Rail.h"
#include "al/rail/RailRider.h"

namespace al {

class RailKeeper {
    Rail* mRail = nullptr;
    RailRider* mRailRider = nullptr;

public:
    RailKeeper(const PlacementInfo& info);
};

} // namespace al