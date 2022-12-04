#pragma once

#include "al/LiveActor/LiveActor.h"
#include <sead/container/seadPtrArray.h>

namespace al {

class LiveActorGroup {
public:
    const char* const mName = nullptr;
    sead::PtrArray<LiveActor> mActors;

    LiveActorGroup(const char* name, int max);
    virtual void registerActor(LiveActor*);
};

} // namespace al