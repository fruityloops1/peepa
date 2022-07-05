#pragma once

#include "al/actor/LiveActor.h"
#include "al/nerve/Nerve.h"
#include "al/util/NerveUtil.h"
#include "hook.hpp"

namespace pe {
namespace util {

    inline const al::Nerve* getNerveAt(uintptr_t offset)
    {
        return (al::Nerve*)exl::util::modules::GetTargetOffset(offset);
    }

    template <uintptr_t nerveOffset>
    void setNerveHook(al::LiveActor* actor)
    {
        const al::Nerve* nerve = getNerveAt(nerveOffset);
        al::setNerve(actor, nerve);
    }

    template <typename To, typename F>
    To getFuncPtrAddr(F ptr)
    {
        struct {
            F ptrType;
            To addr;
        } conv { ptr };
        return conv.addr;
    }

} // namespace
} // namespace