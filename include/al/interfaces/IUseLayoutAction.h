#pragma once

#include "al/interfaces/IUseName.h"
#include "al/layout/LayoutActionKeeper.h"
namespace al {

class IUseLayoutAction : IUseName {
public:
    virtual LayoutActionKeeper* getLayoutActionKeeper() const = 0;
};

} // namespace al