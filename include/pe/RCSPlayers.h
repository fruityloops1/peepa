#pragma once

#include "pe/util/PlayerModelNameUtil.h"

namespace pe {

class RCSPlayers {
public:
    static void initHooks();
    static util::PlayerType& getCurrentPlayerType();
    static void setPlayerType(util::PlayerType type);
};

} // namespace