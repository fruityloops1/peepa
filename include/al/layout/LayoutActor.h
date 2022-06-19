#pragma once

#include "al/interfaces/IUseAudioKeeper.h"
#include "al/interfaces/IUseCamera.h"
#include "al/interfaces/IUseEffectKeeper.h"
#include "al/interfaces/IUseHioNode.h"
#include "al/interfaces/IUseLayout.h"
#include "al/interfaces/IUseLayoutAction.h"
#include "al/interfaces/IUseMessageSystem.h"
#include "al/interfaces/IUseNerve.h"
#include "al/interfaces/IUseSceneObjHolder.h"
#include "al/layout/LayoutPartsActorKeeper.h"
#include "al/layout/LayoutSceneInfo.h"
#include "al/nerve/Nerve.h"

#include <sead/prim/seadSafeString.h>

namespace al {

class LayoutActor : public IUseHioNode,
                    public IUseNerve,
                    public IUseLayout,
                    public IUseLayoutAction,
                    public IUseMessageSystem,
                    public IUseCamera,
                    public IUseAudioKeeper,
                    public IUseEffectKeeper,
                    public IUseSceneObjHolder {
    sead::FixedSafeString<0x80> mName;
    NerveKeeper* mNerveKeeper = nullptr;
    LayoutActionKeeper* mActionKeeper = nullptr;
    class TextPaneAnimator* mTextPaneAnimator = nullptr;
    EffectKeeper* mEffectKeeper = nullptr;
    AudioKeeper* mAudioKeeper = nullptr;
    class LayoutExecuteInfo* mExecuteInfo = nullptr;
    LayoutSceneInfo* mSceneInfo = nullptr;
    LayoutPartsActorKeeper* mPartsActorKeeper = nullptr;
    bool mIsAlive = false;

public:
    LayoutActor(const char* name);

    virtual NerveKeeper* getNerveKeeper() const override;
    virtual void appear();
    virtual void kill();
    virtual void movement();
    virtual void calcAnim(bool);
    virtual const char* getName() const override;
    virtual EffectKeeper* getEffectKeeper() const override;
    virtual AudioKeeper* getAudioKeeper() const override;
    virtual LayoutActionKeeper* getLayoutActionKeeper() const override;
    virtual LayoutKeeper* getLayoutKeeper() const override;
    virtual CameraDirector* getCameraDirector() const override;
    virtual SceneObjHolder* getSceneObjHolder() const override;
    virtual MessageSystem* getMessageSystem() const override;

    void initActionKeeper();
    void initAudioKeeper(AudioKeeper*);
    void initLayoutKeeper(LayoutKeeper*);
    void initLayoutPartsActorKeeper(int);
    void initNerve(const Nerve*, int step);
    void initSceneInfo(LayoutSceneInfo*);
};

} // namespace al