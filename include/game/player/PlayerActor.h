#pragma once

#include "al/actor/LiveActor.h"
#include "al/actor/SubActorKeeper.h"
#include "game/player/Player/Player.h"
#include "game/player/PlayerAnimator.h"
#include "game/player/PlayerModelHolder.h"

class PlayerActor : public al::LiveActor {
    u8 inherits[0x58];

public:
    u8 unk[0x28];
    Player* mPlayer = nullptr;
    u8 unk2[0x10];
    PlayerAnimator* mPlayerAnimator = nullptr;
    u8 unk3[0x58];
    PlayerModelHolder* mModelHolder = nullptr;
};