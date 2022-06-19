#include "pe/RCSPlayers.h"
#include "al/actor/LiveActor.h"
#include "al/util/NerveUtil.h"
#include "lib.hpp"

MAKE_ASM(fightInitFix, R"(
    nop
    nop
    nop
    nop
)");

MAKE_ASM(secondPhaseBowserDefeatCrashFix, "nop");

template <uintptr_t nerveOffset>
static void setNerveHook(al::LiveActor* actor)
{
    al::Nerve* nerve = (al::Nerve*)exl::hook::GetTargetOffset(nerveOffset);
    al::setNerve(actor, nerve);
}

static const char* const getPlayerNameHook()
{
    return "Peach"; /* Mario, Luigi, Peach, Kinopio, Rosetta */
}

void pe::initRCSPlayerHooks()
{
    exl::patch::CodePatcher(0x0040f660).BranchInst(getPlayerNameHook);
    REPLACE_ASM_O(0x0039f580, fightInitFix, 4);
    exl::patch::CodePatcher(0x0039f59c).BranchInst(al::setNerve);
    exl::patch::CodePatcher(0x003a67d0).BranchInst(setNerveHook<0x0137f608>);
    exl::patch::CodePatcher(0x003a7ef4).BranchInst(setNerveHook<0x0137f630>);
    REPLACE_ASM_O(0x00872c68, secondPhaseBowserDefeatCrashFix, 1);
}