#pragma once

#include "al/Audio/AudioDirector.h"
#include "al/Audio/AudioKeeper.h"
#include "al/Nerve/NerveExecutor.h"
#include "al/Scene/Scene.h"
#include "al/Scene/SceneCreator.h"
#include "al/Sequence/SequenceInitInfo.h"

namespace al {

class Sequence : public NerveExecutor, public IUseAudioKeeper, public IUseSceneCreator {
public:
    sead::FixedSafeString<64> mName;
    void* unk1;
    al::Scene* mCurrentScene = nullptr;
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

    AudioDirector* getAudioDirector() const { return mAudioDirector; }

    void setCurrentScene(al::Scene* scene) { mCurrentScene = scene; }
};

} // namespace al