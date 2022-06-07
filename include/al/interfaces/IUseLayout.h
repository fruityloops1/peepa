#pragma once

#include "al/interfaces/IUseName.h"
#include "al/layout/LayoutKeeper.h"

namespace al {

    class IUseLayout : IUseName {
      public:
        virtual LayoutKeeper* getLayoutKeeper() const = 0;
    };

} // namespace al