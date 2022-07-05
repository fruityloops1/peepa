#pragma once

#include "al/actor/LiveActor.h"
#include <sead/prim/seadSafeString.h>

class PlayerAnimator {
public:
    al::LiveActor* mParent = nullptr;
    class PlayerModelHolder* mModelHolder = nullptr;
    void* unkPtr = nullptr;
    class PlayerAnimFrameCtrl* mAnimFrameCtrl = nullptr;
    u8 unk[0x8];
    float mBlendWeights[6];
    u8 unk2[0x10];
    sead::BufferedSafeString mCurAnimName;
    u8 unk3[0x40];
    sead::BufferedSafeString mCurSubAnimName;

    virtual ~PlayerAnimator();
    virtual void vunk1();
    virtual void startAnim(const sead::SafeString&);
    // etc
};