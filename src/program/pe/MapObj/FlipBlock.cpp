#include "pe/MapObj/FlipBlock.h"
#include "al/LiveActor/LiveActorFunction.h"

namespace pe {

void FlipBlock::init(const al::ActorInitInfo& info)
{
    al::initActorWithArchiveName(this, info, "FlipBlock");
    makeActorAppeared();
}

} // namespace pe
