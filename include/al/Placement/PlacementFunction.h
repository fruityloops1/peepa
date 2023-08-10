#pragma once

#include "al/LiveActor/ActorInitInfo.h"
#include "al/Placement/PlacementInfo.h"
#include <sead/math/seadVector.h>

namespace al {

bool tryGetArg(float* out, const al::ActorInitInfo& info, const char* key);
bool tryGetArg(bool* out, const al::ActorInitInfo& info, const char* key);

bool tryGetTrans(sead::Vector3f* out, const PlacementInfo& info);
bool tryGetTrans(sead::Vector3f* out, const ActorInitInfo& info);

} // namespace al