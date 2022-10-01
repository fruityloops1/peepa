#pragma once

#include "al/actor/LiveActor.h"
#include "al/util/StringUtil.h"
#include "al/util/SubActorUtil.h"
#include "game/player/PlayerAnimFunc.h"
#include "game/player/PlayerAnimator.h"
#include "game/player/PlayerModelHolder.h"
#include "pe/util/PlayerModelNameUtil.h"
#include "prim/seadSafeString.h"

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