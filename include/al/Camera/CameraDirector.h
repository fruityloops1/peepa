#pragma once

namespace al {

class CameraDirector {
};

class IUseCamera {
    virtual CameraDirector* getCameraDirector() const = 0;
};

} // namespace al