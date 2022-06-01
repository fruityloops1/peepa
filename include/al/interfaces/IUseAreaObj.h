#pragma once

#include "al/area/AreaObjDirector.h"

namespace al {

    class IUseAreaObj {
        virtual AreaObjDirector* getAreaObjDirector() const = 0;
    };

} // namespace al