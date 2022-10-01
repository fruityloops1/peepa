#pragma once

#include "al/actor/LiveActor.h"

class PlayerModel : public al::LiveActor {
    void* unk1;

public:
    const char* mPlayerName;
    const char* mFigureName;
    u8 unk2[0x80];

    PlayerModel(const char* name, const char* archiveName, const al::ActorInitInfo& info, const char* subArchiveName);
};