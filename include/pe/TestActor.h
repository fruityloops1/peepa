#pragma once

#include "al/actor/LiveActor.h"

namespace pe {

    class TestActor : public al::LiveActor {
      public:
        TestActor(const char* name) : LiveActor(name) {}
        void init(const al::ActorInitInfo& info) override;

        void exeUp();
        void exeDown();
    };

} // namespace pe