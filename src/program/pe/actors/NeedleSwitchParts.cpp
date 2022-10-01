#include "pe/actors/NeedleSwitchParts.h"
#include "al/actors/CollisionObj.h"
#include "al/byaml/PlacementInfo.h"
#include "al/collision/MtxConnector.h"
#include "al/functor/FunctorV0M.h"
#include "al/util/ActorUtil.h"
#include "al/util/ActorUtil/Action.h"
#include "al/util/ActorUtil/Other.h"
#include "al/util/NerveUtil.h"
#include "al/util/PlacementUtil.h"
#include "al/util/SensorUtil/HitSensorUtil.h"
#include "al/util/StageSwitchUtil.h"
#include "al/util/SubActorUtil.h"

namespace pe {

namespace {
    NERVE_DEF(NeedleSwitchParts, End);
    NERVE_DEF(NeedleSwitchParts, Sign);
    NERVE_DEF(NeedleSwitchParts, Attack);
}

void NeedleSwitchParts::init(const al::ActorInitInfo& info)
{
    al::initActor(this, info);

    bool isStartNeedle = false;
    al::tryGetArg(&isStartNeedle, info, "IsStartNeedle");
    al::initNerve(this, isStartNeedle ? (al::Nerve*)&nrvNeedleSwitchPartsAttack : &nrvNeedleSwitchPartsEnd);

    al::initSubActorKeeperNoFile(this, info, 1);
    mNeedleCollision = al::createCollisionObj(this, info, "Needle", al::getHitSensor(this, "CollisionParts"), nullptr);
    al::invalidateCollisionParts(mNeedleCollision);
    al::registerSubActorSyncClipping(this, mNeedleCollision);

    al::listenStageSwitchOn(this, "SwitchKeepOn", al::FunctorV0M<NeedleSwitchParts*, void (NeedleSwitchParts::*)()>(this, &NeedleSwitchParts::start));
    al::listenStageSwitchOff(this, "SwitchKeepOn", al::FunctorV0M<NeedleSwitchParts*, void (NeedleSwitchParts::*)()>(this, &NeedleSwitchParts::end));

    mMtxConnector = al::tryCreateMtxConnector(this, info);

    al::startAction(this, "End");
    mNeedleCollision->makeActorAppeared();
    makeActorAppeared();
}

void NeedleSwitchParts::initAfterPlacement()
{
    if (mMtxConnector)
        al::attachMtxConnectorToCollision(mMtxConnector, this, false);
}

void NeedleSwitchParts::control()
{
    if (mMtxConnector)
        al::connectPoseQT(this, mMtxConnector);
}

void NeedleSwitchParts::start() { al::setNerve(this, &nrvNeedleSwitchPartsSign); }
void NeedleSwitchParts::end() { al::setNerve(this, &nrvNeedleSwitchPartsEnd); }

void NeedleSwitchParts::exeEnd()
{
    if (al::isFirstStep(this))
        al::startAction(this, "End");
    if (al::isActionEnd(this))
        al::invalidateCollisionParts(mNeedleCollision);
}

void NeedleSwitchParts::exeSign()
{
    if (al::isFirstStep(this))
        al::startAction(this, "Sign");
    if (al::isActionEnd(this))
        al::setNerve(this, &nrvNeedleSwitchPartsAttack);
}

void NeedleSwitchParts::exeAttack()
{
    if (al::isFirstStep(this))
        al::startAction(this, "Attack");
    if (al::isActionEnd(this))
        al::validateCollisionParts(mNeedleCollision);
}

} // namespace pe