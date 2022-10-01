#include "pe/actors/puppets/PuppetGeneric.h"
#include "al/util/ActorUtil/Init.h"
#include "al/util/ActorUtil/Other.h"

namespace pe {

void PuppetGeneric::init(const al::ActorInitInfo& info)
{
    al::initActorWithArchiveName(this, info, mArchiveName);
    al::initJointControllerKeeper(this, 32);
    al::invalidateClipping(this);
    makeActorDead();
}

} // namesapce pe