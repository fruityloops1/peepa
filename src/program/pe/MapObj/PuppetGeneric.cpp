#include "pe/MapObj/PuppetGeneric.h"
#include "al/LiveActor/LiveActorFunction.h"

namespace pe {

void PuppetGeneric::init(const al::ActorInitInfo& info)
{
    al::initActorWithArchiveName(this, info, mArchiveName);
    al::initJointControllerKeeper(this, 32);
    al::invalidateClipping(this);
    makeActorDead();
}

} // namesapce pe