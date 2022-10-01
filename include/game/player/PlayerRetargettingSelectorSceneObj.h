#pragma once

#include "al/scene/ISceneObj.h"
#include "game/player/PlayerRetargettingSelector.h"

class PlayerRetargettingSelectorSceneObj : public PlayerRetargettingSelector, public al::ISceneObj {
public:
    const char* getSceneObjName() const override;
};