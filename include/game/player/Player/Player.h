#pragma once

#include "game/player/Player/PlayerFigureDirector.h"
#include "types.h"
#include <sead/math/seadVector.h>

struct PlayerProperty {
    sead::Vector3f trans;
};

class Player {
public:
    PlayerProperty* mPlayerProperty = nullptr;
    u8 unk[0x80];
    PlayerFigureDirector* mFigureDirector = nullptr;
};