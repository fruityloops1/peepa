#pragma once

#include "al/Nerve/NerveKeeper.h"
#include "al/Nerve/NerveStateBase.h"

namespace al {

void setNerve(IUseNerve* p, const Nerve* nerve);

int getNerveStep(const IUseNerve* p);
const Nerve* getCurrentNerve(const IUseNerve* p);
bool isStep(const IUseNerve* p, int step);
bool isNerve(const IUseNerve* p, const Nerve* nerve);
bool isFirstStep(const IUseNerve* p);
bool isLessStep(const IUseNerve* p, int step);
bool isGreaterStep(const IUseNerve* p, int step);
bool isGreaterEqualStep(const IUseNerve* p, int step);

void initNerveState(IUseNerve* p, NerveStateBase* state, const Nerve* stateNrv, const char* name);
bool updateNerveState(IUseNerve* p); // returns if nerve state is dead
bool updateNerveStateAndNextNerve(IUseNerve* p, const Nerve* nerve); // "

} // namespace al

namespace alNerveFunction {

void setNerveAction(al::IUseNerve* p, const char* name);

} // namespace al