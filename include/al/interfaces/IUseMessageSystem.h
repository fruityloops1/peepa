#pragma once

#include "al/message/MessageSystem.h"

namespace al {

    class IUseMessageSystem {
      public:
        virtual MessageSystem* getMessageSystem() const = 0;
    };

} // namespace al