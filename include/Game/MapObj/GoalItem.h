#pragma once

#include "Game/MapObj/Lighthouse.h"
#include "al/LiveActor/LiveActor.h"

class GoalItem : public al::LiveActor {
public:
    GoalItem(const char* name);

    u8 unk[0x24];
    int mScenarioID;
    u8 unk1[0xbc];
    Lighthouse* mLighthouse;
};