#pragma once

#include "al/actor/LiveActor.h"
#include <sead/container/seadPtrArray.h>

namespace al {

    class LiveActorGroup {

        const char* const mName = nullptr;
        sead::PtrArray<LiveActor> mActors;

      public:
        LiveActorGroup(const char* name, int max);
        virtual void registerActor(LiveActor*);
    };

} // namespace al