#pragma once

#include "Game/Player/PlayerAnimFunc.h"
#include "Game/Player/PlayerAnimator.h"
#include "Game/Player/PlayerModelHolder.h"
#include "al/Base/String.h"
#include "al/LiveActor/LiveActor.h"
#include "al/LiveActor/SubActorKeeper.h"
#include "pe/Util/PlayerModelNameUtil.h"
#include <sead/prim/seadSafeString.h>

namespace pe {

class PuppetPlayer : public al::LiveActor {
    const util::PlayerType mPlayerType;
    PlayerModelHolder* mModelHolder = nullptr;
    PlayerAnimator* mPlayerAnimator = nullptr;

public:
    PuppetPlayer(const char* name, util::PlayerType type)
        : LiveActor(name)
        , mPlayerType(type)
    {
    }

    void init(const al::ActorInitInfo& info) override;

    void appear() override;
    void kill() override;

    void control() override;

    void startAnim(const sead::SafeString& anim);
    void startSubAnim(const sead::SafeString& subAnim);

    void change(EPlayerFigure figure);
    inline PlayerModel* getCurrentModel() const { return mModelHolder->mModels[mModelHolder->mCurModelIndex]; }
    inline PlayerAnimator* getPlayerAnimator() const { return mPlayerAnimator; }
};

} // namespace pe