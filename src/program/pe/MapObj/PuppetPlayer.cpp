#include "pe/MapObj/PuppetPlayer.h"
#include "Game/Player/PlayerAnimFunc.h"
#include "Game/Player/PlayerModel.h"
#include "Game/Player/PlayerModelHolder.h"
#include "Game/Player/PlayerRetargettingSelectorSceneObj.h"
#include "al/LiveActor/LiveActor.h"
#include "al/LiveActor/LiveActorFunction.h"
#include "al/Model/SklAnimRetargettingInfo.h"
#include "al/Scene/Scene.h"
#include "al/Se/SeFunction.h"
#include "pe/Puppets.h"
#include "pe/Util/PlayerModelNameUtil.h"

namespace pe {

void PuppetPlayer::init(const al::ActorInitInfo& info)
{
    al::initActorSceneInfo(this, info);
    al::initActorPoseTRSV(this);
    al::initActorSRT(this, info);
    al::initActorClipping(this, info);
    al::initExecutorEnemyMovement(this, info);
    al::initActorModelKeeper(this, info, "ObjectData/Mario", 6, "ObjectData/MarioAnimation");

    mModelHolder = new PlayerModelHolder(sizeof(util::sPowerUpNames) / sizeof(util::sPowerUpNames[0]));
    PlayerRetargettingSelectorSceneObj* retargettingSelector = static_cast<PlayerRetargettingSelectorSceneObj*>(al::getSceneObj(this, 0x19));

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
            const char* archiveName = util::getPlayerArchiveName(mPlayerType, type);
            PlayerModel* model = new PlayerModel(archiveName, archiveName, info, nullptr);
            model->mPlayerName = util::getPlayerName(mPlayerType);
            model->mFigureName = util::getPowerUpName(type);
            mModelHolder->registerModel(i, model);
            mModelHolder->initCurrentModel(0);
            al::setSeSeqLocalVariableDefault(model, 0, (int)mPlayerType);
            al::addPartialSklAnimPartsListRecursive(model, "Spine1", 0);
            al::startAction(model, "Wait");
            model->makeActorDead();

            if (util::isFigureClimb(type))
                mModelHolder->validateTailDynamics();
            i++;
        }
    }

    mPlayerAnimator = new PlayerAnimator(this, mModelHolder, retargettingSelector);
    mPlayerAnimator->init();
    initCollider(80.f, 0.f, 0);
    al::onCollide(this);

    al::invalidateClipping(this);
}

void PuppetPlayer::appear()
{
    LiveActor::appear();
    mModelHolder->mModels[mModelHolder->mCurModelIndex]->appear();
}

void PuppetPlayer::kill()
{
    LiveActor::kill();
    mModelHolder->mModels[mModelHolder->mCurModelIndex]->kill();
}

void PuppetPlayer::control()
{
    // mPlayerAnimator->update(); // garbage
    if (mPlayerAnimator->mIsSubAnim && mPlayerAnimator->isSubAnimEnd())
        mPlayerAnimator->endSubAnim();
}

void PuppetPlayer::change(EPlayerFigure type)
{
    mModelHolder->change((int)type);
}

void PuppetPlayer::startAnim(const sead::SafeString& anim)
{
    auto& s = getPuppetHookState();
    s.isStartAnimHookEnabled = false;
    mPlayerAnimator->startAnim(anim);
    s.isStartAnimHookEnabled = true;
}

void PuppetPlayer::startSubAnim(const sead::SafeString& subAnim)
{
    auto& s = getPuppetHookState();
    s.isStartAnimHookEnabled = false;
    mPlayerAnimator->startSubAnim(subAnim);
    s.isStartAnimHookEnabled = true;
}

} // namespace pe