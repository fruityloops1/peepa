#pragma once

#include "Game/Player/PlayerActor.h"
#include "al/LiveActor/LiveActor.h"

namespace al {

class PlayerHolder {
    struct Player;
    Player* mPlayers = nullptr;
    int mBufferSize = 0;

public:
    int mPlayerNum = 0;

    PlayerHolder(int bufferSize);
    LiveActor* tryGetPlayer(int index);
};

int getPlayerNumMax(const LiveActor*);
PlayerActor* getPlayerActor(const LiveActor*, int index);

} // namespace al
