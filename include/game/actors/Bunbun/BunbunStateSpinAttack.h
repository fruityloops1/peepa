#pragma once

#include "al/actor/ActorInitInfo.h"
#include "al/nerve/ActorStateBase.h"

class Bunbun;
class BunbunStateSpinAttack : public al::ActorStateBase {

public:
    Bunbun* mBunbun = nullptr;
    al::LiveActor* mSpinArm = nullptr;

    BunbunStateSpinAttack(Bunbun* parent, const al::ActorInitInfo& info);

    void exeAttack();
    void exeAttackEnd();
    void exeAttackSign();
    void exeAttackStart();
};