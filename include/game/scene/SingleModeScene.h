#pragma once

#include "game/actors/RaidonSurf.h"
#include "game/scene/StageSceneBase.h"

class SingleModeScene : public StageSceneBase {
public:
    void movement() override;

    u8 unk[0x18c];
    RaidonSurf* mRaidonSurf = nullptr;
};