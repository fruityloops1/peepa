#pragma once

#include "al/LiveActor/LiveActor.h"

namespace al {

class PlayerHolder {
    struct Player* mPlayers = nullptr;
    int mBufferSize = 0;

public:
    int mPlayerNum = 0;

    PlayerHolder(int bufferSize);
    LiveActor* tryGetPlayer(int index);
};

} // namespace al