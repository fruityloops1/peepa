#pragma once

#include "al/actor/ActorInitInfo.h"

namespace al {

int calcLinkChildNum(const al::ActorInitInfo& info, const char* linkName);

bool tryGetArg(float* out, const al::ActorInitInfo& info, const char* key);
bool tryGetArg(bool* out, const al::ActorInitInfo& info, const char* key);

} // namespace al