#pragma once

#include "al/Nerve/NerveStateBase.h"

namespace al {

template <typename T>
class HostStateBase : public NerveStateBase {
    T* const mHost = nullptr;

public:
    HostStateBase(T* host)
        : mHost(host)
    {
    }
};

} // namespace al