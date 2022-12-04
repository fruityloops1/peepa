#pragma once

#include "al/Nerve/Nerve.h"
#include "al/Nerve/NerveFunction.h"
#include "util/modules.hpp"
#include <cstdint>

namespace pe {
namespace util {

    inline const al::Nerve* getNerveAt(uintptr_t offset)
    {
        return (al::Nerve*)exl::util::modules::GetTargetOffset(offset);
    }

    inline const void setNerveAt(al::IUseNerve* to, uintptr_t offset)
    {
        al::setNerve(to, getNerveAt(offset));
    }

} // namespace util
} // namespace pe