#pragma once

#include "al/actor/ActorInitInfo.h"
#include <sead/math/seadVector.h>

namespace al {

void getLinksInfo(PlacementInfo* out, const PlacementInfo& parentInfo, const char* linkName);
int calcLinkChildNum(const al::ActorInitInfo& info, const char* linkName);

bool tryGetArg(float* out, const al::ActorInitInfo& info, const char* key);
bool tryGetArg(bool* out, const al::ActorInitInfo& info, const char* key);

bool tryGetTrans(sead::Vector3f* out, const PlacementInfo& info);
bool tryGetTrans(sead::Vector3f* out, const ActorInitInfo& info);

} // namespace al