#pragma once

#include "al/area/AreaObjDirector.h"
#include "al/camera/CameraDirector.h"
#include "al/collision/CollisionDirector.h"
#include "al/scene/SceneObjHolder.h"
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