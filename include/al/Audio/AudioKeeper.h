#pragma once

namespace al {

class AudioKeeper {
};

class IUseAudioKeeper {
    virtual AudioKeeper* getAudioKeeper() const = 0;
};

} // namespace al