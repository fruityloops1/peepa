#pragma once

#include "al/Layout/LayoutInitInfo.h"
#include "al/Placement/PlacementInfo.h"

namespace al {

class ActorInitInfo {
    const PlacementInfo* mPlacementInfo = nullptr;
    const LayoutInitInfo* mLayoutInitInfo = nullptr;
    void* unk[25];

public:
    ActorInitInfo() = default;

    void initNoViewId(const PlacementInfo*, const ActorInitInfo&);
};

const PlacementInfo& getPlacementInfo(const ActorInitInfo& info);
const LayoutInitInfo& getLayoutInitInfo(const ActorInitInfo& info);

} // namespace al