#include "pe/Client/MPClient.h"
#include "Game/MapObj/DisasterModeController.h"
#include "Game/Player/PlayerAnimFunc.h"
#include "al/LiveActor/LiveActorFunction.h"
#include "al/Nerve/Nerve.h"
#include "pe/Client/ServerScene.h"
#include "pe/MapObj/PuppetGeneric.h"
#include "pe/MapObj/PuppetPlayer.h"
#include "pe/Puppets.h"
#include "pe/Util/Nerve.h"
#include "rc/Util/SceneObjUtil.h"
#include "util/modules.hpp"
#include <cstring>

namespace pe {

MPClient& MPClient::instance()
{
    static MPClient client;
    return client;
}

namespace {
    class Log : public OutPacket {
        const char* const mData = nullptr;

    public:
        Log(const char* data)
            : OutPacket(2)
            , mData(data)
        {
        }
        size_t calcSize() { return strlen(mData) + 1; }
        void construct(u8* out) { strcpy((char*)out, mData); }
    };
}

void MPClient::log(const char* msg)
{
    Log packet = Log(msg);
    sendPacket(packet);
}

void MPClient::receivePlayerUpdate(u8* data, size_t size)
{
    struct {
        u64 playerId;
        sead::Vector3f trans;
        sead::Vector3f rotate;
        sead::Vector3f scale;
        bool isSurfingRaidon : 1 = false;
        EPlayerFigure figure : 4;
    } packetData = *(typeof(packetData)*)data;
    tryAddPlayer(packetData.playerId);

    pe::PlayerInfo& player = mServerScene.getPlayer(packetData.playerId);
    pe::PuppetPlayer* puppet = player.puppet;
    PlayerModel* model = puppet->getCurrentModel();

    if (al::isDead(puppet))
        puppet->appear();

    player.lastTrans = player.trans;
    player.trans = packetData.trans;
    player.rotate = packetData.rotate;
    player.lerpFrame = 0;
    player.isSurfingRaidon = packetData.isSurfingRaidon;

    al::setRotate(model, player.rotate);
    al::setScale(model, player.scale);
    puppet->change(packetData.figure);
}

void MPClient::receivePlayerAnimStart(u8* data, size_t size)
{
    struct {
        u64 playerId;
        bool isSubAnim : 1;
        u8 frame : 7;
    } packetData = *(typeof(packetData)*)data;
    tryAddPlayer(packetData.playerId);

    const char* animName = (const char*)&data[sizeof(packetData)];
    pe::PuppetPlayer* puppet = mServerScene.getPlayer(packetData.playerId).puppet;

    if (packetData.isSubAnim)
        puppet->startSubAnim(animName);
    else
        puppet->startAnim(animName);
}

void MPClient::receivePlayerDisasterTimerUpdate(u8* data, size_t size)
{
    struct {
        u64 playerId;
        int mFramesOfProsperityTransition;
        int mFramesOfProsperity;
        int mFramesOfAnticipationTransition;
        int mFramesOfAnticipation;
        int mFramesOfDisasterTransition;
        int mFramesOfDisaster;
        int unk1;
        int mFramesSinceLastEvent;
        uintptr_t currentNerveOffset;
    } packetData = *(typeof(packetData)*)data;
    tryAddPlayer(packetData.playerId);

    PuppetPlayer* puppet = mServerScene.getPlayer(packetData.playerId).puppet;
    DisasterModeController* controller = rc::getDisasterModeController(puppet);
    if (controller) {
        const al::Nerve* currentNerve = pe::util::getNerveAt(packetData.currentNerveOffset);
        controller->mFramesOfProsperityTransition = packetData.mFramesOfProsperityTransition;
        controller->mFramesOfProsperity = packetData.mFramesOfProsperity;
        controller->mFramesOfAnticipationTransition = packetData.mFramesOfAnticipationTransition;
        controller->mFramesOfAnticipation = packetData.mFramesOfAnticipation;
        controller->mFramesOfDisasterTransition = packetData.mFramesOfDisasterTransition;
        controller->mFramesOfDisaster = packetData.mFramesOfDisaster;
        controller->unk1 = packetData.unk1;
        controller->mFramesSinceLastEvent = packetData.mFramesSinceLastEvent;
        if (!al::isNerve(controller, currentNerve)
            && packetData.currentNerveOffset != 0x01318b88
            && packetData.currentNerveOffset != 0x01318ac0
            && packetData.currentNerveOffset != 0x01318b68 /* fix screen white glitch */)
            al::setNerve(controller, currentNerve);
    }
}

void MPClient::receivePlayerConnectionStatus(u8* data, size_t size)
{
    struct {
        u64 playerId;
        bool isDisconnect : 1;
    } packetData = *(typeof(packetData)*)data;

    if (packetData.isDisconnect) {
        if (PlayerInfo* player = mServerScene.tryGetPlayer(packetData.playerId)) {
            player->puppet->kill();
            player->raidonPuppet->kill();
            player->koopaJrPuppet->kill();
            pe::MPClient::instance().log("Unregistered %.8lx ", player->id);
            *player = PlayerInfo();
        }
    } else
        tryAddPlayer(packetData.playerId);
}

void MPClient::receivePlayerGenericPuppetUpdate(u8* data, size_t size)
{
    struct {
        u64 playerId;
        PuppetType type : 7;
        bool isDead : 1;
        sead::Vector3f trans;
        sead::Quatf quat;
    } packetData = *(typeof(packetData)*)data;
    tryAddPlayer(packetData.playerId);

    PlayerInfo& player = mServerScene.getPlayer(packetData.playerId);
    PuppetGeneric* puppet = player.getGenericPuppet(packetData.type);

    packetData.isDead ? puppet->kill() : puppet->appear();

    puppet->mDestTrans = packetData.trans;
    al::setQuat(puppet, packetData.quat);
    // al::calcJointPos(al::getTransPtr(playerPuppet), puppet, "Player1");
}

void MPClient::receivePlayerGenericPuppetAnimStart(u8* data, size_t size)
{
    struct {
        u64 playerId;
        PuppetType type;
        u8 frame;
    } packetData = *(typeof(packetData)*)data;
    tryAddPlayer(packetData.playerId);
    const char* animName = (const char*)&data[sizeof(packetData)];

    PlayerInfo& player = mServerScene.getPlayer(packetData.playerId);
    PuppetGeneric* puppet = player.getGenericPuppet(packetData.type);

    al::tryStartAction(puppet, animName);
}

void MPClient::tryAddPlayer(u64 id)
{
    for (PlayerInfo& player : mServerScene.players)
        if (player.id == id)
            return;
    for (PlayerInfo& player : mServerScene.players)
        if (player.id == -1) {
            player = PlayerInfo();
            player.id = id;
            player.puppet = mServerScene.getFreePuppet(pe::util::PlayerType::Mario);
            player.raidonPuppet = mServerScene.getFreeRaidonPuppet();
            player.koopaJrPuppet = mServerScene.getFreeKoopaJrPuppet();
            return;
        }
    pe::MPClient::instance().log("Couldn't add %lx to %lx %lx %lx %lx ", id, mServerScene.players[0].id, mServerScene.players[1].id, mServerScene.players[2].id, mServerScene.players[3].id);
}

} // namespace fl