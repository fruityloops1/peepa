#pragma once

#include "Game/MapObj/RaidonSurf.h"
#include "Game/Scene/StageSceneBase.h"

class SingleModeScene : public StageSceneBase {
public:
    void movement() override;

    u8 unk[0x18c];
    RaidonSurf* mRaidonSurf = nullptr;
};