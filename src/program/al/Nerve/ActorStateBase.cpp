#include "al/Nerve/ActorStateBase.h"

namespace al {

ActorStateBase::ActorStateBase(const char* name, LiveActor* parent)
    : NerveStateBase(name)
    , mParent(parent)
{
}

} // namespace al