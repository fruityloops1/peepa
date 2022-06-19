#pragma once

#include "al/interfaces/IUseRail.h"
#include "al/rail/RailRider.h"
namespace al {

class RailKeeper : IUseRail {
    RailRider* mRailRider = nullptr;

public:
    al::RailRider* getRailRider() const override { return mRailRider; }
};

} // namespace al