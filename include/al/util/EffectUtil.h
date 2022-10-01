#pragma once

#include "al/interfaces/IUseEffectKeeper.h"

namespace al {

void tryDeleteEffect(IUseEffectKeeper*, const char* effectName);

} // namespace al