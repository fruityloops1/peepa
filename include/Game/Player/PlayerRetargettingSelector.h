#pragma once

#include "Game/Player/IUsePlayerRetargettingSelector.h"
#include "Game/Player/PlayerAnimFunc.h"
#include "al/Model/SklAnimRetargettingInfo.h"
#include <sead/basis/seadTypes.h>
#include <sead/container/seadPtrArray.h>

class PlayerRetargettingSelector : public IUsePlayerRetargettingSelector {
    void* inherit;
    sead::PtrArray<int> unkPtrArray1;
    sead::PtrArray<int> unkPtrArray2;
    sead::PtrArray<int> unkPtrArray3;

public:
    virtual al::SklAnimRetargettingInfo* createRetargettingInfo(const char*, EPlayerFigure);
    virtual al::SklAnimRetargettingInfo* createDemoRetargettingInfo(const char*, EPlayerFigure);
    void applyDefaultRetargettingInfo(al::LiveActor*, int) override;
    void applyCharaRetargettingInfo(al::LiveActor*, int) override;
    void applyFigureRetargettingInfo(al::LiveActor*, int) override;
    al::SklAnimRetargettingInfo* getDefaultRetargettingInfo(int) override;
    al::SklAnimRetargettingInfo* getCharaRetargettingInfo(int) override;
    al::SklAnimRetargettingInfo* getFigureRetargettingInfo(int) override;

    static const char* getFileName();
};