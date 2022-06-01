#pragma once

#include "al/camera/CameraDirector.h"

namespace al {

    class IUseCamera {
        virtual CameraDirector* getCameraDirector() const = 0;
    };

} // namespace al