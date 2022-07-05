#include "pe/actors/PuppetPlayer.h"
#include "al/actor/LiveActor.h"
#include "al/util/ActorUtil.h"
#include "al/util/ActorUtil/Action.h"
#include "al/util/ActorUtil/Sound.h"
#include "al/util/SubActorUtil.h"
#include "game/player/PlayerAnimFunc.h"
#include "game/player/PlayerModel.h"
#include "game/player/PlayerModelHolder.h"
#include "pe/util/PlayerModelNameUtil.h"

namespace pe {

void PuppetPlayer::init(const al::ActorInitInfo& info)
{
    al::initActorSceneInfo(this, info);
    al::initActorPoseTRSV(this);
    al::initActorSRT(this, info);
    al::initActorClipping(this, info);
    al::initActorSceneInfo(this, info);
    al::initActorPoseTRSV(this);
    al::initActorSRT(this, info);
    al::initActorClipping(this, info);
    al::initExecutorEnemyMovement(this, info);

    mModelHolder = new PlayerModelHolder(sizeof(util::sPowerUpNames) / sizeof(util::sPowerUpNames[0]));

    {
        int i = 0;
        for (EPlayerFigure type : {
                 EPlayerFigure::None,
                 EPlayerFigure::Mini,
                 EPlayerFigure::Fire,
                 EPlayerFigure::Climb,
                 EPlayerFigure::RaccoonDog,
                 EPlayerFigure::Boomerang,
                 EPlayerFigure::RaccoonDogWhite,
                 EPlayerFigure::Manekineko,
                 EPlayerFigure::ClimbWhite,
                 EPlayerFigure::ClimbGiga }) {
            const char* archiveName = pe::util::getPlayerArchiveName(mPlayerType, type);
            PlayerModel* model = new PlayerModel(archiveName, archiveName, info, nullptr);
            mModelHolder->registerModel(i, model);
            al::setSeSeqLocalVariableDefault(model, 0, (int)mPlayerType);
            al::addPartialSklAnimPartsListRecursive(model, "Spine1", 0);
            al::startAction(mModelHolder->mModels[mModelHolder->mCurModelIndex], "Wait");
            al::clearSklAnimInterpole(model);
            mModelHolder->initCurrentModel(0);
            if (util::isFigureClimb(type))
                mModelHolder->validateTailDynamics();
            i++;
        }
    }

    al::invalidateClipping(this);
    makeActorAppeared();
}

void PuppetPlayer::control()
{
}

void PuppetPlayer::startAction(const char* actionName)
{
    PlayerModel* model = mModelHolder->mModels[mModelHolder->mCurModelIndex];

    if (al::tryStartActionIfNotPlaying(model, actionName)) {
        const char* action = al::getActionName(model);
        if (action && al::isSklAnimExist(model, action))
            al::clearSklAnimInterpole(model);
    }
}

void PuppetPlayer::startSubAction(int subActorIndex, const char* actionName)
{
    PlayerModel* model = mModelHolder->mModels[mModelHolder->mCurModelIndex];

    al::LiveActor* subActor = al::getSubActor(model, subActorIndex);
    const char* action = al::getActionName(model);
    if (subActor && action
        && al::tryStartActionIfNotPlaying(subActor, actionName)
        && al::isSklAnimExist(model, actionName))
        al::clearSklAnimInterpole(model);
}

} // namespace pe