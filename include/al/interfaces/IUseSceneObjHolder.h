#pragma once

#include "al/scene/SceneObjHolder.h"

namespace al {

class IUseSceneObjHolder {
public:
    virtual SceneObjHolder* getSceneObjHolder() const = 0;
};

} // namespace al