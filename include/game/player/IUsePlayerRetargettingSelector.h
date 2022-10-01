#pragma once

#include "al/actor/LiveActor.h"
#include "al/model/SklAnimRetargettingInfo.h"

// wtf is IUsePlayerRetargettingInfoCreator and why isn't it this smh nintendo
class IUsePlayerRetargettingSelector {
public:
    virtual void applyDefaultRetargettingInfo(al::LiveActor*, int);
    virtual void applyCharaRetargettingInfo(al::LiveActor*, int);
    virtual void applyFigureRetargettingInfo(al::LiveActor*, int);
    virtual al::SklAnimRetargettingInfo* getDefaultRetargettingInfo(int);
    virtual al::SklAnimRetargettingInfo* getCharaRetargettingInfo(int);
    virtual al::SklAnimRetargettingInfo* getFigureRetargettingInfo(int);
};