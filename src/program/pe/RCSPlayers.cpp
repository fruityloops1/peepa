#include "pe/RCSPlayers.h"
#include "al/actor/LiveActor.h"
#include "al/util/NerveUtil.h"
#include "lib.hpp"
#include "pe/util/Hooks.h"

static const char* getPlayerNameHook(int index) { return pe::util::sPlayerNames[(int)pe::RCSPlayers::getCurrentPlayerType()]; }

PATCH_DEFINE_ASM(FightInitFix, R"(
    nop
    nop
    nop
    nop
)");

void pe::RCSPlayers::initHooks()
{
    using Patcher = exl::patch::CodePatcher;
    using namespace exl::armv8::inst;

    Patcher(0x0040f660).BranchInst((void*)getPlayerNameHook);
    FightInitFix::InstallAtOffset(0x0039f580);

    Patcher(0x00872c68).WriteInst(Nop()); // phase 2 bowser defeat crash fix
    Patcher(0x0039f59c).BranchInst((void*)al::setNerve);
    Patcher(0x003a67d0).BranchInst((void*)pe::util::setNerveHook<0x0137f608>);
    Patcher(0x003a7ef4).BranchInst((void*)pe::util::setNerveHook<0x0137f630>);
}

pe::util::PlayerType& pe::RCSPlayers::getCurrentPlayerType()
{
    static util::PlayerType type { util::PlayerType::Mario };
    return type;
}

void pe::RCSPlayers::setPlayerType(util::PlayerType type)
{
    getCurrentPlayerType() = type;
}