#pragma once

#include "al/model/SklAnimRetargettingInfo.h"
#include "game/player/PlayerAnimFunc.h"
#include <sead/basis/seadTypes.h>
#include <sead/container/seadPtrArray.h>

class PlayerRetargettingSelector {
    void* inherit;
    sead::PtrArray<int> unkPtrArray1;
    sead::PtrArray<int> unkPtrArray2;
    sead::PtrArray<int> unkPtrArray3;

public:
    virtual al::SklAnimRetargettingInfo* createRetargettingInfo(const char*, EPlayerFigure);
};