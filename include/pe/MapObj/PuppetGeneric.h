#pragma once

#include "al/LiveActor/LiveActor.h"

namespace pe {

class PuppetGeneric : public al::LiveActor {
    const char* const mArchiveName = nullptr;

public:
    sead::Vector3f mDestTrans;

    PuppetGeneric(const char* name, const char* archiveName)
        : LiveActor(name)
        , mArchiveName(archiveName)
    {
    }
    void init(const al::ActorInitInfo& info) override;
};

} // namespace pe