#pragma once

#include <sead/container/seadPtrArray.h>

namespace al {

class LiveActor;
class ActorInitInfo;

class SubActorKeeper {
public:
    LiveActor* mParent = nullptr;
    sead::PtrArray<LiveActor> mSubActors;

    SubActorKeeper(al::LiveActor* actor, const al::ActorInitInfo& info, const char*, int);

    static SubActorKeeper* tryCreate(al::LiveActor* actor, const al::ActorInitInfo& info, const char*, int);
};

} // namespace al