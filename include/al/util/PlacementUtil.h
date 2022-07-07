#pragma once

#include "al/actor/ActorInitInfo.h"

namespace al {

int calcLinkChildNum(const al::ActorInitInfo& info, const char* linkName);

} // namespace al