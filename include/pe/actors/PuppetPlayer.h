#pragma once

#include "al/actor/LiveActor.h"
#include "al/util/StringUtil.h"
#include "al/util/SubActorUtil.h"
#include "game/player/PlayerModelHolder.h"
#include "pe/util/PlayerModelNameUtil.h"

namespace pe {

class PuppetPlayer : public al::LiveActor {
    const util::PlayerType mPlayerType;

public:
    PlayerModelHolder* mModelHolder = nullptr;

    PuppetPlayer(const char* name, util::PlayerType type)
        : LiveActor(name)
        , mPlayerType(type)
    {
    }

    void init(const al::ActorInitInfo& info) override;
    void control() override;

    void startAction(const char* actionName);
    void startSubAction(int subActorIndex, const char* actionName);

    inline al::LiveActor* tryGetSubActor(const char* subActorName)
    {
        PlayerModel* model = mModelHolder->mModels[mModelHolder->mCurModelIndex];
        for (int i = 0; i < al::getSubActorNum(model); i++) {
            al::LiveActor* subActor = al::getSubActor(model, i);
            if (al::isEqualString(subActor->getName(), subActorName))
                return subActor;
        }
        return nullptr;
    }
};

} // namespace pe