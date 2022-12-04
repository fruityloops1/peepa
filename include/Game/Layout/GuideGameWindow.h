#pragma once

#include "Game/Layout/WindowMessage.h"
#include "al/Scene/ISceneObj.h"

class GuideGameWindow : public al::ISceneObj {
    void* unk;

public:
    WindowMessage* mWindow = nullptr;

    const char* getSceneObjName() const override; // ガイドウィンドウ
};