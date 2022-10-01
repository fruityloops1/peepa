#pragma once

#include "al/actor/LiveActor.h"
#include "al/actors/CollisionObj.h"
#include "al/collision/MtxConnector.h"

namespace pe {

class NeedleSwitchParts : public al::LiveActor {
    al::CollisionObj* mNeedleCollision = nullptr;
    al::MtxConnector* mMtxConnector = nullptr;

public:
    NeedleSwitchParts(const char* name)
        : LiveActor(name)
    {
    }

    void init(const al::ActorInitInfo& info) override;
    void initAfterPlacement() override;
    void control() override;

    void start();
    void end();

    void exeEnd();
    void exeSign();
    void exeAttack();
};

} // namespace pe