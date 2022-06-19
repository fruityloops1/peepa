#include "pe/TestActor.h"
#include "al/util/ActorUtil.h"
#include "al/util/ActorUtil/Pose.h"
#include "al/util/NerveUtil.h"

namespace pe {

namespace {
    NERVE_DEF(TestActor, Up);
    NERVE_DEF(TestActor, Down);
} // namespace

void TestActor::init(const al::ActorInitInfo& info)
{
    al::initActor(this, info);
    al::initNerve(this, &nrvTestActorUp, 0);

    makeActorAppeared();
}

void TestActor::exeUp()
{
    al::getTransPtr(this)->y += 10;
    if (al::isStep(this, 60))
        al::setNerve(this, &nrvTestActorDown);
}
void TestActor::exeDown()
{
    al::getTransPtr(this)->y -= 10;
    if (al::isStep(this, 60))
        al::setNerve(this, &nrvTestActorUp);
}

} // namespace pe