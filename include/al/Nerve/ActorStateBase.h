#pragma once

#include "al/LiveActor/LiveActor.h"
#include "al/Nerve/NerveStateBase.h"

namespace al {

class ActorStateBase : public NerveStateBase {
    LiveActor* const mParent = nullptr;

public:
    ActorStateBase(const char* name, LiveActor* parent);
};

} // namespace al