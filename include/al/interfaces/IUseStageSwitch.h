#pragma once

#include "al/interfaces/IUseName.h"
#include "al/stage/StageSwitchKeeper.h"

namespace al {

    class IUseStageSwitch : IUseName {
        virtual StageSwitchKeeper* getStageSwitchKeeper() const = 0;
        virtual void initStageSwitchKeeper() = 0;
    };

} // namespace al