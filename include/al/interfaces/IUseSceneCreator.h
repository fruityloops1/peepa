#pragma once

#include "al/scene/SceneCreator.h"

namespace al {

class IUseSceneCreator {
public:
    virtual ~IUseSceneCreator();
    virtual SceneCreator* getSceneCreator() const = 0;
    virtual void setSceneCreator(SceneCreator*) = 0;
};

} // namespace al