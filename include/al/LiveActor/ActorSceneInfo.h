#pragma once

#include "al/AreaObj/AreaObjDirector.h"
#include "al/Camera/CameraDirector.h"
#include "al/Collision/CollisionDirector.h"
#include "al/Scene/SceneObjHolder.h"
#include "types.h"

namespace al {

struct ActorSceneInfo {
    SceneObjHolder* mSceneObjHolder = nullptr;
    void* gap = nullptr;
    CollisionDirector* mCollisionDirector = nullptr;
    void* gap2 = nullptr;
    CameraDirector* mCameraDirector = nullptr;
    void* gap3 = nullptr;
    void* gap4 = nullptr;
    void* gap5 = nullptr;
    void* gap6 = nullptr;
    AreaObjDirector* mAreaObjDirector = nullptr;
    void* gap7 = nullptr;
    void* gap8 = nullptr;
    void* unk = nullptr;
};

} // namespace al