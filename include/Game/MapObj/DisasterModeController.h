#pragma once

#include "Game/MapObj/BlackSun.h"
#include "al/LiveActor/LiveActor.h"
#include "al/Scene/SceneObjHolder.h"

class DisasterModeController : public al::LiveActor, public al::ISceneObj {
public:
    u8 unk[0x58];
    int mFramesOfProsperityTransition;
    int mFramesOfProsperity;
    int mFramesOfAnticipationTransition;
    int mFramesOfAnticipation;
    int mFramesOfDisasterTransition;
    int mFramesOfDisaster;
    int unk1;
    int mFramesSinceLastEvent;
    u8 unk2[0x24];
    BlackSun* mBlackSun = nullptr;
    u8 unk3[0x03];
    bool mDisableClock;
};