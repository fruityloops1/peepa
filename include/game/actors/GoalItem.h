#pragma once

#include "al/actor/LiveActor.h"
#include "game/actors/Lighthouse.h"

class GoalItem : public al::LiveActor {
public:
    GoalItem(const char* name);

    u8 unk[0x24];
    int mScenarioID;
    u8 unk1[0xbc];
    Lighthouse* mLighthouse;
};