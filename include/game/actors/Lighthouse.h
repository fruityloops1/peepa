#pragma once

#include "al/actor/LiveActor.h"

class Lighthouse : public al::LiveActor {
public:
    Lighthouse(const char* name);

    u8 unk[0x68];
    int mNextScenarioID;
};