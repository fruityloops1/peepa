#include "Game/Sequence/ProductSequence.h"
#include "al/Nerve/Nerve.h"
#include "al/Nerve/NerveFunction.h"
#include "al/Nerve/NerveStateCtrl.h"
#include "patch/code_patcher.hpp"
#include "pe/Client/MPClient.h"
#include "pe/Util/Nerve.h"

namespace {

NERVE_DEF(ProductSequence, Test);

} // namespace

const al::Nerve* ProductSequence::getTestNrv() { return &nrvProductSequenceTest; }

void ProductSequence::exeTest()
{
    // pe::MPClient::instance().log("al::isFirstStep: 0x%.8x", al::isFirstStep);
    // pe::MPClient::instance().log("al::updateNerveState: 0x%.8x", al::updateNerveState);
    // al::setNerve(this, pe::util::getNerveAt(0x0138cf78));

    if (al::updateNerveState(this))
        al::setNerve(this, pe::util::getNerveAt(0x0138cf78));
}

static void setTestNerveHook(al::IUseNerve* p)
{
    pe::MPClient::instance().log("SET NERVE TEST HOOK THING");
    al::setNerve(p, &nrvProductSequenceTest);
}

void installProductSequenceHooks()
{
    exl::patch::CodePatcher(0x003fd3bc).BranchInst((void*)setTestNerveHook);
}
