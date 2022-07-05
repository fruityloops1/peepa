#pragma once

#include "game/player/Player/PlayerFigureDirector.h"
#include "types.h"

class Player {
public:
    u8 inherits[0x60];
    u8 unk[0x28];
    PlayerFigureDirector* mFigureDirector = nullptr;
};