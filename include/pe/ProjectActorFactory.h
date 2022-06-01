#pragma once

#include "al/actor/LiveActor.h"
#include "game/factory/ProjectActorFactory.h"

namespace pe {

    class ProjectActorFactory : public ::ProjectActorFactory {
      public:
        ProjectActorFactory();
    };

    template <typename T>
    al::LiveActor* createActorFunction(const char* name) {
        return new T(name);
    }

} // namespace pe