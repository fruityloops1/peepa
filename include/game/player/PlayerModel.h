#pragma once

#include "al/actor/LiveActor.h"

class PlayerModel : public al::LiveActor {
    u8 unk[0x98];

public:
    PlayerModel(const char* name, const char* archiveName, const al::ActorInitInfo& info, const char* subArchiveName);
};