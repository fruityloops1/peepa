#include "pe/RCSPlayers.h"
#include "al/actor/LiveActor.h"
#include "al/util/NerveUtil.h"
#include "lib.hpp"
#include "pe/util/Hooks.h"

MAKE_ASM(fightInitFix, R"(
    nop
    nop
    nop
    nop
)");

MAKE_ASM(secondPhaseBowserDefeatCrashFix, "nop");

static const char* const getPlayerNameHook()
{
    return "Peach"; /* Mario, Luigi, Peach, Kinopio, Rosetta */
}

void pe::initRCSPlayerHooks()
{
    exl::patch::CodePatcher(0x0040f660).BranchInst((void*)getPlayerNameHook);
    // REPLACE_ASM_O(0x0039f580, fightInitFix, 4);
    exl::patch::CodePatcher(0x0039f59c).BranchInst((void*)al::setNerve);
    exl::patch::CodePatcher(0x003a67d0).BranchInst((void*)pe::util::setNerveHook<0x0137f608>);
    exl::patch::CodePatcher(0x003a7ef4).BranchInst((void*)pe::util::setNerveHook<0x0137f630>);
    // REPLACE_ASM_O(0x00872c68, secondPhaseBowserDefeatCrashFix, 1);
}