#pragma once

#include "al/LiveActor/LiveActor.h"

namespace pe {

class FlipBlock : public al::LiveActor {
public:
    FlipBlock(const char* name)
        : LiveActor(name)
    {
    }
    void init(const al::ActorInitInfo& info) override;
};

} // namespace pe
