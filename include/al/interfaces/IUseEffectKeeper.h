#pragma once

#include "al/effect/EffectKeeper.h"

namespace al {

    class IUseEffectKeeper {
        virtual EffectKeeper* getEffectKeeper() const = 0;
    };

} // namespace al