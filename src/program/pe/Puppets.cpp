#include "pe/Puppets.h"
#include "al/actor/LiveActor.h"
#include "al/interfaces/IUseNerve.h"
#include "al/util/ActorUtil.h"
#include "al/util/ActorUtil/Action.h"
#include "al/util/InputUtil.h"
#include "al/util/MathUtil.h"
#include "al/util/StringUtil.h"
#include "game/actors/KoopaJr.h"
#include "game/actors/RaidonSurf.h"
#include "game/player/PlayerActor.h"
#include "game/player/PlayerAnimFunc.h"
#include "game/scene/SingleModeScene.h"
#include "math/seadVector.h"
#include "patch/code_patcher.hpp"
#include "pe/actors/puppets/PuppetGeneric.h"
#include "pe/client/MPClient.h"
#include "pe/util/Hooks.h"
#include "pe/util/PlayerModelNameUtil.h"
#include "prim/seadSafeString.h"
#include "rc/util/SceneObjUtil.h"

namespace pe {

PuppetHookState& getPuppetHookState()
{
    static PuppetHookState state;
    return state;
}

void initPuppets(const al::ActorInitInfo& info)
{
    int i = 0;
    for (pe::util::PlayerType type : {
             pe::util::PlayerType::Mario }) {
        for (int j = 0; j < 3; j++) {
            pe::PuppetPlayer*& puppet = pe::MPClient::instance().mServerScene.puppets[i][j];
            puppet = new pe::PuppetPlayer("Player Puppet", type);
            al::initCreateActorNoPlacementInfo(puppet, info);
        }
        i++;
    }

    for (pe::PuppetGeneric*& raidonPuppet : pe::MPClient::instance().mServerScene.raidonPuppets) {
        raidonPuppet = new pe::PuppetGeneric("Plessie Puppet", "RaidonSurf");
        al::initCreateActorNoPlacementInfo(raidonPuppet, info);
    }
    for (pe::PuppetGeneric*& koopaJrPuppet : pe::MPClient::instance().mServerScene.koopaJrPuppets) {
        koopaJrPuppet = new pe::PuppetGeneric("Bowser Jr. Puppet", "KoopaJr");
        al::initCreateActorNoPlacementInfo(koopaJrPuppet, info);
        koopaJrPuppet->initCollider(80.0f, 35.0f, 0);
    }
}

namespace {

    class PlayerUpdate : public pe::OutPacket {
        struct {
            sead::Vector3f trans;
            sead::Vector3f rotate;
            sead::Vector3f scale;
            bool isSurfingRaidon : 1 = false;
            EPlayerFigure figure : 4;
        } mData;

    public:
        PlayerUpdate(const sead::Vector3f& trans, const sead::Vector3f& rotate, const sead::Vector3f& scale, bool isSurfingRaidon, EPlayerFigure figure)
            : pe::OutPacket(3)
        {
            mData.trans = trans;
            mData.rotate = rotate;
            mData.scale = scale;
            mData.isSurfingRaidon = isSurfingRaidon;
            mData.figure = figure;
        }

        size_t calcSize() override
        {
            return sizeof(mData);
        }
        void construct(u8* out) override
        {
            *(typeof(mData)*)out = mData;
        }
    };

    class PlayerAnimStart : public pe::OutPacket {
    public:
        enum AnimType : u8 {
            Anim,
            SubAnim
        };

    private:
        struct {
            AnimType type : 1;
            u8 frame : 7;
        } mData;
        const char* const mAnimName;

    public:
        PlayerAnimStart(const char* animName, AnimType type, int frame)
            : pe::OutPacket(4)
            , mAnimName(animName)
        {
            mData.frame = frame;
            mData.type = type;
        }
        size_t calcSize() override
        {
            return sizeof(mData) + strlen(mAnimName) + 1;
        }
        void construct(u8* out) override
        {
            *(typeof(mData)*)out = mData;
            strcpy((char*)&out[sizeof(mData)], mAnimName);
        }
    };

    class PlayerGenericPuppetUpdate : public pe::OutPacket {
        struct {
            PuppetType type : 7;
            bool isDead : 1;
            sead::Vector3f trans;
            sead::Quatf quat;
        } mData;

    public:
        PlayerGenericPuppetUpdate(PuppetType type, bool isDead, const sead::Vector3f& trans, const sead::Quatf& quat)
            : pe::OutPacket(6)
        {
            mData.type = type;
            mData.isDead = isDead;
            mData.trans = trans;
            mData.quat = quat;
        }

        size_t calcSize() override
        {
            return sizeof(mData);
        }
        void construct(u8* out) override
        {
            *(typeof(mData)*)out = mData;
        }
    };

    class PlayerGenericPuppetAnimStart : public pe::OutPacket {
        struct {
            PuppetType type;
            u8 frame;
        } mData;
        const char* const mAnimName;

    public:
        PlayerGenericPuppetAnimStart(PuppetType type, const char* animName, int frame)
            : pe::OutPacket(7)
            , mAnimName(animName)
        {
            mData.type = type;
            mData.frame = frame;
        }
        size_t calcSize() override
        {
            return sizeof(mData) + strlen(mAnimName) + 1;
        }
        void construct(u8* out) override
        {
            *(typeof(mData)*)out = mData;
            strcpy((char*)&out[sizeof(mData)], mAnimName);
        }
    };
}

static bool isSurfingRaidon = false;

static void raidonGetOnHook(al::IUseNerve* t, al::Nerve* nerve)
{
    isSurfingRaidon = true;
    al::setNerve(t, nerve);
}

static void raidonGetOffHook(al::IUseNerve* t, al::Nerve* nerve)
{
    isSurfingRaidon = false;
    al::setNerve(t, nerve);
}

MAKE_HOOK_T(void, startAnimHook, (PlayerAnimator * animator, const sead::SafeString& anim), {
    if (getPuppetHookState().isStartAnimHookEnabled) {
        PlayerAnimStart packet(anim.cstr(), PlayerAnimStart::AnimType::Anim, 0);
        pe::MPClient::instance().sendPacket(packet);
    }
    impl(animator, anim);
});

MAKE_HOOK_T(void, startSubAnimHook, (PlayerAnimator * animator, const sead::SafeString& subAnim), {
    if (getPuppetHookState().isStartAnimHookEnabled) {
        PlayerAnimStart packet(subAnim.cstr(), PlayerAnimStart::AnimType::SubAnim, 0);
        pe::MPClient::instance().sendPacket(packet);
    }
    impl(animator, subAnim);
});

void initPuppetHooks()
{
    exl::patch::CodePatcher(0x003bd0a0).BranchLinkInst((void*)raidonGetOnHook);
    exl::patch::CodePatcher(0x003bd494).BranchLinkInst((void*)raidonGetOffHook);

    INJECT_HOOK_T(0x003747a0, startAnimHook);
    INJECT_HOOK_T(0x00374c60, startSubAnimHook);
}

static void sendPlayerUpdatePacket(PlayerActor* player)
{
    PlayerUpdate packet(al::getTrans(player), al::getRotate(player), al::getScale(player), isSurfingRaidon, player->mPlayer->mFigureDirector->mCurFigure);
    pe::MPClient::instance().sendPacket(packet);
}

void updatePuppets(SingleModeScene* scene)
{
    PlayerActor* player = static_cast<PlayerActor*>(scene->mLiveActorKit->mPlayerHolder->tryGetPlayer(0));
    pe::MPClient& client = pe::MPClient::instance();
    RaidonSurf* raidon = scene->mRaidonSurf;
    KoopaJr* koopaJr = rc::getKoopaJr(scene);
    al::LiveActor* boomerang = player->mBoomerangHolder->boomerang;

    RUN_EACH(4, {
        // send player puppet updates
        const sead::Vector3f& vel = al::getVelocity(player);
        static bool lastFrameSent = false;
        if (std::abs(vel.x) > 0.1 or std::abs(vel.y) > 0.05 or std::abs(vel.z) > 0.1) {
            sendPlayerUpdatePacket(player);
            if (!pe::MPClient::instance().isConnected())
                pe::MPClient::instance().reconnect();
            lastFrameSent = true;
        } else if (lastFrameSent) {
            lastFrameSent = false;
            sendPlayerUpdatePacket(player);
        }

        if (raidon) {
            // send plessie puppet updates
            const sead::Vector3f& vel = al::getVelocity(raidon);
            static bool isDead = al::isDead(raidon);
            if (isDead != al::isDead(raidon)
                or std::abs(vel.x) > 0.1 or std::abs(vel.y) > 0.05 or std::abs(vel.z) > 0.1) {
                PlayerGenericPuppetUpdate packet(PuppetType::RaidonSurf, al::isDead(raidon), al::getTrans(raidon), al::getQuat(raidon));
                client.sendPacket(packet);
            }
            isDead = al::isDead(raidon);
        }
        if (koopaJr) {
            // send bowser jr. puppet updates
            const sead::Vector3f& vel = al::getVelocity(koopaJr);
            static bool isDead = al::isDead(koopaJr);
            if (isDead != al::isDead(koopaJr)
                or std::abs(vel.x) > 0.1 or std::abs(vel.y) > 0.05 or std::abs(vel.z) > 0.1) {
                PlayerGenericPuppetUpdate packet(PuppetType::KoopaJr, al::isDead(koopaJr), al::getTrans(koopaJr), al::getQuat(koopaJr));
                client.sendPacket(packet);
            }
            isDead = al::isDead(koopaJr);
        }
    });

    if (raidon) {
        // send plessie animations
        static const char* lastRaidonAnim = "";
        const char* raidonAnim = al::getActionName(scene->mRaidonSurf);
        if (!al::isEqualString(lastRaidonAnim, raidonAnim)) {
            PlayerGenericPuppetAnimStart packet(PuppetType::RaidonSurf, raidonAnim, al::getActionFrame(raidon));
            client.sendPacket(packet);
            PlayerGenericPuppetUpdate packet2(PuppetType::RaidonSurf, al::isDead(raidon), al::getTrans(raidon), al::getQuat(raidon));
            client.sendPacket(packet2);
        }
        lastRaidonAnim = raidonAnim;
    }

    if (koopaJr) {
        // send bowser jr. animations
        static const char* lastKoopaJrAnim = "";
        const char* koopaJrAnim = al::getActionName(koopaJr);
        if (lastKoopaJrAnim && koopaJrAnim && (!al::isEqualString(lastKoopaJrAnim, koopaJrAnim))) {
            PlayerGenericPuppetAnimStart packet(PuppetType::KoopaJr, koopaJrAnim, al::getActionFrame(koopaJr));
            client.sendPacket(packet);
            PlayerGenericPuppetUpdate packet2(PuppetType::KoopaJr, al::isDead(koopaJr), al::getTrans(koopaJr), al::getQuat(koopaJr));
            client.sendPacket(packet2);
        }
        lastKoopaJrAnim = koopaJrAnim;
    }

    // lerp player puppets / teleport to plessie bone
    for (pe::PlayerInfo& info : client.mServerScene.players) {
        pe::PuppetPlayer* puppet = info.puppet;
        if (puppet == nullptr or info.id == -1)
            continue;
        if (info.isSurfingRaidon) {
            al::calcJointPos(al::getTransPtr(puppet->getCurrentModel()), info.raidonPuppet, "Player1");
            continue;
        }
        if (puppet->getCurrentModel() == nullptr)
            continue;

        if (info.lerpFrame == 4)
            al::setTrans(puppet->getCurrentModel(), info.trans);
        else {
            al::lerpVec(al::getTransPtr(puppet->getCurrentModel()), info.lastTrans, info.trans, info.lerpFrame * (1.0 / 5));
            info.lerpFrame++;
        }
    }

    // lerp plessie puppets
    for (pe::PuppetGeneric* puppet : client.mServerScene.raidonPuppets)
        if (puppet)
            al::lerpVec(al::getTransPtr(puppet), al::getTrans(puppet), puppet->mDestTrans, 0.25);
    // lerp bowser jr. puppets
    for (pe::PuppetGeneric* puppet : client.mServerScene.koopaJrPuppets)
        if (puppet)
            al::lerpVec(al::getTransPtr(puppet), al::getTrans(puppet), puppet->mDestTrans, 0.25);
}

} // namespace pe