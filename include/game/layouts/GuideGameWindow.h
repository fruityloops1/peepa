#pragma once

#include "al/scene/ISceneObj.h"
#include "game/layouts/WindowMessage.h"

class GuideGameWindow : public al::ISceneObj {
    void* unk;

public:
    WindowMessage* mWindow = nullptr;

    const char* getSceneObjName() const override; // ガイドウィンドウ
};