#pragma once

namespace al {

class CollisionDirector {
};

class IUseCollision {
    virtual CollisionDirector* getCollisionDirector() const = 0;
};

} // namespace al