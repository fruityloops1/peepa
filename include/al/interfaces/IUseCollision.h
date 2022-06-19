#pragma once

#include "al/collision/CollisionDirector.h"

namespace al {

class IUseCollision {
    virtual CollisionDirector* getCollisionDirector() const = 0;
};

} // namespace al