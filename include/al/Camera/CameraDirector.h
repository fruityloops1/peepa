#pragma once

namespace al {

class CameraDirector {
};

class IUseCamera {
    virtual void* getSceneCameraInfo() const = 0;
};

} // namespace al
