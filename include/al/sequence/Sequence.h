#pragma once

#include "al/audio/AudioDirector.h"
#include "al/audio/AudioKeeper.h"
#include "al/interfaces/IUseAudioKeeper.h"
#include "al/interfaces/IUseSceneCreator.h"
#include "al/nerve/NerveExecutor.h"
#include "al/scene/Scene.h"
#include "al/scene/SceneCreator.h"
#include "al/sequence/SequenceInitInfo.h"

namespace al {

class Sequence : public NerveExecutor, public IUseAudioKeeper, public IUseSceneCreator {
public:
    sead::FixedSafeString<64> mName;
    al::Scene* mCurScene = nullptr;
    void* unk1;
    SceneCreator* mSceneCreator = nullptr;
    AudioDirector* mAudioDirector = nullptr;
    AudioKeeper* mAudioKeeper = nullptr;
    void* unk2;
    bool mIsAlive = true;

    ~Sequence() override;
    virtual void init(const SequenceInitInfo& info);
    virtual void update();
    virtual void kill();
    virtual void drawMain();
    virtual void drawSub();
    AudioKeeper* getAudioKeeper() const override;
    virtual bool isDisposable() const;
    virtual Scene* getCurrentScene() const;

private:
    virtual bool vunk1();

public:
    SceneCreator* getSceneCreator() const override;
    void setSceneCreator(SceneCreator*) override;
};

} // namespace al