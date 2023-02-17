#pragma once

#include "Game/Scene/LuigiBrosScene.h"
#include "Game/Sequence/ProductSequence.h"
#include "Game/Sequence/StageWipeKeeper.h"
#include "al/Nerve/HostStateBase.h"
#include "al/Scene/SceneCreator.h"
#include "al/Screen/ScreenCaptureExecutor.h"

namespace pe {

class ProductStateTest : public al::HostStateBase<ProductSequence>, public al::IUseSceneCreator {
    al::SceneCreator* mSceneCreator = nullptr;
    StageWipeKeeper* mWipeKeeper = nullptr;
    LuigiBrosScene* mScene = nullptr;
    void* _40 = nullptr;
    void* _48 = nullptr;

public:
    ProductStateTest(ProductSequence* host, void* unk1, const al::SequenceInitInfo& info, void* unk2, GameDataHolder* gameDataHolder, StageWipeKeeper* stageWipeKeeper, al::ScreenCaptureExecutor* screenCaptureExecutor);

    void init() override;
    void appear() override;
    al::SceneCreator* getSceneCreator() const override { return mSceneCreator; }
    void setSceneCreator(al::SceneCreator* p) override { mSceneCreator = p; }

    void exeLoad();
    void exeWait();
};

void installProductStateTestHooks();

} // namespace pe
