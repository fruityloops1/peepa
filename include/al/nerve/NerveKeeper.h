#pragma once

#include "al/interfaces/IUseNerve.h"
#include "al/nerve/Nerve.h"
#include "al/nerve/NerveStateCtrl.h"

namespace al {

class NerveActionCtrl;
class NerveKeeper {
public:
    NerveKeeper(void*, const Nerve*, int);

    void update();
    void setNerve(const Nerve*);
    const Nerve* getCurrentNerve();
    void initNerveAction(al::NerveActionCtrl*);

    IUseNerve* mParent = nullptr;

private:
    const Nerve* mLastNerve = nullptr;
    const Nerve* mNerve = nullptr;
    s32 mStep = 0;
    s32 _1c;
    NerveStateCtrl* mNerveStateCtrl = nullptr;
    NerveActionCtrl* mNerveActionCtrl = nullptr;
};

} // namespace al