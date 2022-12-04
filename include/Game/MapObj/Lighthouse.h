#pragma once

#include "al/LiveActor/LiveActor.h"

class Lighthouse : public al::LiveActor {
public:
    Lighthouse(const char* name);

    u8 unk[0x68];
    int mNextScenarioID;
};