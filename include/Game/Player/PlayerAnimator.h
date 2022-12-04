#pragma once

#include "Game/Player/IUsePlayerRetargettingSelector.h"
#include "Game/Player/PlayerModelHolder.h"
#include "al/LiveActor/LiveActor.h"
#include <sead/prim/seadSafeString.h>

class PlayerAnimator {
public:
    al::LiveActor* mParent = nullptr;
    PlayerModelHolder* mModelHolder = nullptr;
    IUsePlayerRetargettingSelector* mRetargettingSelector = nullptr;
    class PlayerAnimFrameCtrl* mAnimFrameCtrl = nullptr;
    bool mIsSubAnim;
    u8 unk[0x7];
    float mBlendWeights[6];
    u8 unk2[0x10];
    sead::BufferedSafeString mCurAnimName;
    u8 unk3[0x40];
    sead::BufferedSafeString mCurSubAnimName;
    u8 unk4[0xa0];

    PlayerAnimator(al::LiveActor* parent, PlayerModelHolder* modelHolder, IUsePlayerRetargettingSelector* retargettingSelector);

    void init();
    void update();

    virtual ~PlayerAnimator();

private:
    virtual void vunk1();

public:
    virtual void startAnim(const sead::SafeString& anim);
    virtual void setAnimRate(float rate);
    virtual void setAnimRateCommon(float rate);
    virtual void setAnimFrame(float frame);
    virtual bool isAnimEnd() const;
    virtual bool isAnim(const sead::SafeString& anim) const;
    virtual bool isAnimReverse() const;
    virtual float getAnimFrame() const;
    virtual float getAnimFrameMax() const;
    virtual void clearInterpolation();
    virtual const char* getAnimName() const;
    virtual void startSubAnim(const sead::SafeString& subAnim);
    virtual void endSubAnim();
    virtual bool isSubAnimBinding() const;
    virtual bool isSubAnimEnd() const;
    virtual bool isSubAnim(const sead::SafeString& subAnim) const;
    virtual bool isSubAnimReverse() const;
    virtual float getSubAnimFrame() const;
    virtual float getAnimFrameMax(const sead::SafeString& anim) const;
    virtual void startMaterialAnim(const sead::SafeString& mclAnim);
    virtual bool isMaterialAnimEnd() const;
    virtual void setWeightSixfold(float, float, float, float, float, float);
    virtual float getWeight(int index) const;

private:
    virtual void vunk2();
    // etc
};