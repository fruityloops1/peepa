#pragma once

#include "al/scene/LiveActorGroup.h"
#include "al/scene/PlayerHolder.h"

namespace al {

class LiveActorKit {

public:
    int _0; // max liveactors?
    int _4; // max players?
    void* _8 = nullptr;
    void* _10 = nullptr;
    void* _18 = nullptr;
    void* _20 = nullptr;
    void* _28 = nullptr;
    void* _30 = nullptr;
    void* _38 = nullptr;
    void* _40 = nullptr;
    void* _48 = nullptr;
    PlayerHolder* mPlayerHolder = nullptr;
    void* _58 = nullptr;
    void* _60 = nullptr;
    void* _68 = nullptr;
    void* _70 = nullptr;
    void* _78 = nullptr;
    LiveActorGroup* mLiveActorGroup = nullptr;
    void* _88 = nullptr;
    void* _90 = nullptr;
    void* _98 = nullptr;
    u8 _a0;
    u8 _a1;

    LiveActorKit(int, int, u8, u8);

    void init(int);
    void initGraphics(const class GraphicsInitArg&, const char*);
    void endInit();
};

} // namespace al