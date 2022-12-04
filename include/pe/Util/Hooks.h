#pragma once

#include "al/LiveActor/LiveActor.h"
#include "pe/Util/Nerve.h"
#include "util/modules.hpp"

#define RUN_EACH(I, FUNC)                      \
    {                                          \
        static int isdasdasdasdasdasdfsdf = 0; \
        isdasdasdasdasdasdfsdf++;              \
        if (isdasdasdasdasdasdfsdf >= I) {     \
            isdasdasdasdasdasdfsdf = 0;        \
            {                                  \
                FUNC                           \
            }                                  \
        }                                      \
    }

namespace pe {
namespace util {

    template <uintptr_t nerveOffset>
    void setNerveHook(al::LiveActor* actor)
    {
        const al::Nerve* nerve = util::getNerveAt(nerveOffset);
        al::setNerve(actor, nerve);
    }

    template <typename F>
    uintptr_t getFuncPtrOffset(F ptr)
    {
        struct {
            F ptrType;
            uintptr_t offset;
        } conv { ptr };
        return conv.offset - exl::util::modules::GetTargetStart();
    }

} // namespace
} // namespace