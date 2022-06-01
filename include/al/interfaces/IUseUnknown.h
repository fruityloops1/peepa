#pragma once

namespace al {

    class IUseUnknown {
        virtual void* getUnknown() const = 0;
    };

} // namespace al