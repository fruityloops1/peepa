#pragma once

#include "al/actor/LiveActor.h"
#include "al/nerve/Nerve.h"

namespace al {

    void initNerve(al::LiveActor* actor, const Nerve* nerve, int step);

} // namespace al