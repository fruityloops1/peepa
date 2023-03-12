#pragma once

namespace al {

class CameraDirector_RS {
};

class IUseCamera_RS {
    virtual CameraDirector_RS* getCameraDirector_RS() const = 0;
};

} // namespace al
