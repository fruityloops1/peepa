#include "al/nerve/NerveStateBase.h"
#include "al/nerve/Nerve.h"

namespace al {

NerveStateBase::NerveStateBase(const char* name)
    : NerveExecutor(name)
    , mIsDead(true)
{
}

void NerveStateBase::init() { }
void NerveStateBase::appear() { mIsDead = false; }
void NerveStateBase::kill() { mIsDead = true; }

bool NerveStateBase::update()
{
    updateNerve();
    if (!mIsDead)
        control();
    return mIsDead;
}

void NerveStateBase::control() { }

} // namespace al