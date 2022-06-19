#pragma once

#include "al/interfaces/IUseNerve.h"
#include "al/nerve/Nerve.h"
#include "al/nerve/NerveStateCtrl.h"
#include "types.h"

namespace al {

class NerveKeeper {
public:
    NerveKeeper(IUseNerve*, const Nerve*, int);

    void update();

    const Nerve* getCurrentNerve();
    void setNerve(const Nerve*);

    IUseNerve* mParent;

private:
    const Nerve* mLastNerve = nullptr;
    const Nerve* mNerve = nullptr;
    s32 mStep = 0;
    s32 _1c;
    NerveStateCtrl* mNerveStateCtrl = nullptr;
    void* _28;
};

} // namespace al