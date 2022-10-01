#pragma once

#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"

class WindowProcessing : public al::LayoutActor {
    u8 unk[0x8];
    int mProcessFrames;
    void* unk2;

public:
    WindowProcessing(const al::LayoutInitInfo& info, const char* = nullptr);

    void appearWithSystemMessage(const char* msbt, const char* message, int frames, bool);
};