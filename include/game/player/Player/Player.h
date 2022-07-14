#pragma once

#include "game/player/Player/PlayerFigureDirector.h"
#include <sead/math/seadVector.h>

struct PlayerProperty {
    sead::Vector3f trans;
    u8 unk[0x18];
    sead::Vector3f velocity;
};

class Player {
public:
    PlayerProperty* mPlayerProperty = nullptr;
    u8 unk[0x80];
    PlayerFigureDirector* mFigureDirector = nullptr;
};