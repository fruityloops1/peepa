#pragma once

#include "al/Functor/FunctorBase.h"
#include "al/Util/IUseName.h"

namespace al {

class StageSwitchKeeper {
};

class IUseStageSwitch : IUseName {
    virtual StageSwitchKeeper* getStageSwitchKeeper() const = 0;
    virtual void initStageSwitchKeeper() = 0;
};

bool tryOnStageSwitch(al::IUseStageSwitch*, const char* name);
bool tryOffStageSwitch(al::IUseStageSwitch*, const char* name);
void listenStageSwitchOn(al::IUseStageSwitch*, const char* name, const al::FunctorBase&);
void listenStageSwitchOff(al::IUseStageSwitch*, const char* name, const al::FunctorBase&);

} // namespace al