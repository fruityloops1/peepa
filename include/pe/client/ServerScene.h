#pragma once

#include "diag/assert.hpp"
#include "pe/Puppets.h"
#include "pe/actors/puppets/PuppetGeneric.h"
#include "pe/actors/puppets/PuppetPlayer.h"
#include "pe/util/PlayerModelNameUtil.h"

namespace pe {

struct PlayerInfo {
    sead::Vector3f trans = sead::Vector3f::zero, lastTrans = sead::Vector3f::zero, scale = { 1, 1, 1 };
    sead::Vector3f rotate = sead::Vector3f::zero;
    int lerpFrame = 0;
    bool isSurfingRaidon = false;

    pe::PuppetPlayer* puppet = nullptr;
    pe::PuppetGeneric* raidonPuppet = nullptr;
    pe::PuppetGeneric* koopaJrPuppet = nullptr;

    inline pe::PuppetGeneric* getGenericPuppet(PuppetType type)
    {
        switch (type) {
        case PuppetType::RaidonSurf:
            return raidonPuppet;
        case PuppetType::KoopaJr:
            return koopaJrPuppet;
        default:
            return nullptr;
        }
    }

    u64 id = -1;
};

struct ServerScene {
    pe::PuppetPlayer* puppets[5][3];
    PlayerInfo players[5];

    pe::PuppetGeneric* raidonPuppets[4] { nullptr };
    pe::PuppetGeneric* koopaJrPuppets[4] { nullptr };

    inline PlayerInfo* tryGetPlayer(u64 id)
    {
        for (PlayerInfo& info : players)
            if (info.id == id)
                return &info;
        return nullptr;
    }

    inline PlayerInfo& getPlayer(u64 id)
    {
        PlayerInfo* player = tryGetPlayer(id);
        if (player)
            return *player;
        EXL_ABORT(0x23);
    }

    inline bool isPuppetUsed(const pe::PuppetPlayer* puppet) const
    {
        for (const PlayerInfo& info : players)
            if (info.puppet == puppet)
                return true;
        return false;
    }

    inline bool isGenericPuppetUsed(const pe::PuppetGeneric* puppet) const
    {
        for (const PlayerInfo& info : players)
            if (info.raidonPuppet == puppet || info.koopaJrPuppet == puppet)
                return true;
        return false;
    }

    inline PuppetPlayer* getFreePuppet(pe::util::PlayerType type)
    {
        for (PuppetPlayer* puppet : puppets[(int)type])
            if (!isPuppetUsed(puppet))
                return puppet;
        return nullptr;
    }

    inline PuppetGeneric* getFreeRaidonPuppet()
    {
        for (PuppetGeneric* puppet : raidonPuppets)
            if (!isGenericPuppetUsed(puppet))
                return puppet;
        return nullptr;
    }
    inline PuppetGeneric* getFreeKoopaJrPuppet()
    {
        for (PuppetGeneric* puppet : koopaJrPuppets)
            if (!isGenericPuppetUsed(puppet))
                return puppet;
        return nullptr;
    }
};

} // namespace pe