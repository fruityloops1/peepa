#pragma once

#include "al/actor/LiveActor.h"
#include "al/interfaces/IUseSceneObjHolder.h"
#include "al/scene/ISceneObj.h"
#include "game/actors/BlackSun.h"

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

    static DisasterModeController* getDisasterModeController(al::IUseSceneObjHolder*);
};