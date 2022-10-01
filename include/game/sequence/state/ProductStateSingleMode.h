#pragma once

#include "al/interfaces/IUseSceneCreator.h"
#include "al/nerve/HostStateBase.h"
#include "al/scene/SceneCreator.h"
#include "al/sequence/SequenceInitInfo.h"
#include <sead/basis/seadTypes.h>

class ProductSequence;
class ProductStateSingleMode : public al::HostStateBase<ProductSequence>, public al::IUseSceneCreator {
    struct ProductStageStartParam* mStartParam;
    void* unk1[2];
    al::SequenceInitInfo* mSequenceInitInfo;
    void* unk2;
    al::SceneCreator* mSceneCreator;

public:
    void init() override;
    void appear() override;
    void kill() override;
    al::SceneCreator* getSceneCreator() const override;
    void setSceneCreator(al::SceneCreator*) override;
};