#pragma once

#include "al/functor/FunctorBase.h"
#include "al/interfaces/IUseStageSwitch.h"

namespace al {

bool tryOnStageSwitch(al::IUseStageSwitch*, const char* name);
void listenStageSwitchOn(al::IUseStageSwitch*, const char* name, const al::FunctorBase&);
void listenStageSwitchOff(al::IUseStageSwitch*, const char* name, const al::FunctorBase&);

} // namespace al