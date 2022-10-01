#pragma once

#include "al/byaml/PlacementInfo.h"
#include "al/layout/LayoutInitInfo.h"

namespace al {

class ActorInitInfo {
    const PlacementInfo* mPlacementInfo = nullptr;
    const LayoutInitInfo* mLayoutInitInfo = nullptr;
    void* unk[25];

public:
    ActorInitInfo() = default;
};

const PlacementInfo& getPlacementInfo(const ActorInitInfo& info);
const LayoutInitInfo& getLayoutInitInfo(const ActorInitInfo& info);

} // namespace al