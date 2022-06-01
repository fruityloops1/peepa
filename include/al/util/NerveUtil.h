#pragma once

#include "al/nerve/NerveKeeper.h"

#define NERVE_DEF(CLASS, ACTION)                                                                                       \
    struct CLASS##Nrv##ACTION : public al::Nerve {                                                                     \
        inline void execute(al::NerveKeeper* keeper) override { static_cast<CLASS*>(keeper->mParent)->exe##ACTION(); } \
    };                                                                                                                 \
    const CLASS##Nrv##ACTION nrv##CLASS##ACTION;

namespace al {

    void setNerve(IUseNerve* parent, const Nerve* nerve);
    bool isNerve(const IUseNerve* parent, const Nerve* nerve);
    const Nerve* getCurrentNerve(const IUseNerve* parent);

    int getNerveStep(const IUseNerve* parent);
    bool isFirstStep(const IUseNerve* parent);
    bool isStep(const IUseNerve* parent, int step);

} // namespace al