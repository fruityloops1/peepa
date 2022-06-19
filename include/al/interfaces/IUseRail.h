#pragma once

#include "al/rail/RailRider.h"

namespace al {

class IUseRail {
    virtual RailRider* getRailRider() const = 0;
};

} // namespace al