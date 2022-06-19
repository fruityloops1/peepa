#pragma once

#include "al/audio/AudioKeeper.h"

namespace al {

class IUseAudioKeeper {
    virtual AudioKeeper* getAudioKeeper() const = 0;
};

} // namespace al