#pragma once

#include "al/actor/LiveActor.h"

namespace al {

class PlayerHolder {
    struct Player* mPlayers = nullptr;
    int mBufferSize = 0;
    int mPlayerNum = 0;

public:
    PlayerHolder(int bufferSize);
    LiveActor* tryGetPlayer(int index);
};

} // namespace al