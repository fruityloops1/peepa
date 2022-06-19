#pragma once

#include "al/audio/AudioKeeper.h"
#include "al/interfaces/IUseAudioKeeper.h"
#include "al/interfaces/IUseCamera.h"
#include "al/interfaces/IUseSceneObjHolder.h"
#include "al/nerve/NerveExecutor.h"
#include "al/scene/LiveActorKit.h"
#include "al/scene/SceneInitInfo.h"
#include "al/scene/SceneObjHolder.h"
#include <sead/prim/seadSafeString.h>

namespace al {

class Scene : NerveExecutor, IUseAudioKeeper, IUseCamera, IUseSceneObjHolder {
    sead::FixedSafeString<64> mName;
    bool mIsAlive = false;
    class StageResourceKeeper* mStageResourceKeeper = nullptr;
    LiveActorKit* mLiveActorKit = nullptr;
    class LayoutKit* mLayoutKit = nullptr;
    SceneObjHolder* mSceneObjHolder = nullptr;
    class SceneStopCtrl* mSceneStopCtrl = nullptr;
    class AudioDirector* mAudioDirector = nullptr;
    AudioKeeper* mAudioKeeper = nullptr;
    class ScreenCoverCtrl* mScreenCoverCtrl = nullptr;
    class DrawSystemInfo* mDrawSystemInfo = nullptr;

    void* unk_d0 = nullptr;
    void* unk_d8 = nullptr;
    u8 unk_e0;

public:
    virtual ~Scene();
    virtual void init(const SceneInitInfo& info);
    virtual void appear();
    virtual void kill();
    virtual void movement();
    virtual void control();
    virtual AudioKeeper* getAudioKeeper() const override;
    virtual SceneObjHolder* getSceneObjHolder() const override;
    virtual CameraDirector* getCameraDirector() const override;

private:
    virtual bool unk_58();
    virtual bool unk_60();

public:
    virtual void drawMain();
    virtual void drawSub();
};

} // namespace al