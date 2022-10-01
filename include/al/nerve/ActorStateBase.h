#pragma once

#include "al/actor/LiveActor.h"
#include "al/nerve/NerveStateBase.h"

namespace al {

class ActorStateBase : public NerveStateBase {
    LiveActor* const mParent = nullptr;

public:
    ActorStateBase(const char* name, LiveActor* parent);
};

} // namespace al