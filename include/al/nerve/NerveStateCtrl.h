#pragma once

#include "al/nerve/NerveStateBase.h"

namespace al {

struct State {
    al::NerveStateBase* mNerveStateBase;
    const al::Nerve* mNerve;
    const char* mName;
};

class NerveStateCtrl {
public:
    NerveStateCtrl(int);

    void addState(al::NerveStateBase*, const al::Nerve*, const char*);
    bool updateCurrentState();
    void startState(const al::Nerve*);
    void update();

    State* findStateInfo(const al::Nerve*);
    bool isCurrentStateEnd() const;
    void tryEndCurrentState();

    int _0;
    int mStateCount;
    State* mStates;
    State* mCurrentState;
};

} // namespace al