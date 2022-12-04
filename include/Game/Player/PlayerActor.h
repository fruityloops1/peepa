#pragma once

#include "Game/Player/Player/Player.h"
#include "Game/Player/PlayerAnimator.h"
#include "Game/Player/PlayerModelHolder.h"
#include "al/Collision/Collider.h"
#include "al/LiveActor/LiveActor.h"
#include "al/LiveActor/SubActorKeeper.h"

class PlayerActor : public al::LiveActor {
    u8 inherits[0x58];

public:
    u8 unk[0x28];
    Player* mPlayer = nullptr;
    u8 unk2[0x10];
    PlayerAnimator* mPlayerAnimator = nullptr;
    u8 unk3[0x58];
    PlayerModelHolder* mModelHolder = nullptr;
    void* unk4[0x4];
    struct {
        void* unk;
        al::LiveActor* boomerang = nullptr;
    }* mBoomerangHolder = nullptr;
    u8 unk5[0x98];
    al::Collider* mCollider = nullptr;
};