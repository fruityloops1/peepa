#pragma once

#include "al/actor/LiveActor.h"
#include "game/actors/Bunbun/BunbunStateShellAttack.h"
#include "game/actors/Bunbun/BunbunStateSpinAttack.h"

class Bunbun : public al::LiveActor {
    void* unk;
    al::ActorStateBase* mStateStartDemo = nullptr;
    BunbunStateShellAttack* mStateShellAttack = nullptr;
    BunbunStateSpinAttack* mStateSpinAttack = nullptr;

public:
    Bunbun(const char* name);

    void control() override;
};