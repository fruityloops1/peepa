#include "pe/RCSMultiplayer.h"
#include "al/util/ActorUtil/Item.h"
#include "al/util/InputUtil.h"
#include "al/util/NerveUtil.h"
#include "game/actors/DisasterModeController.h"
#include "game/layouts/WindowMessage.h"
#include "game/player/PlayerActor.h"
#include "lib.hpp"
#include "pe/client/MPClient.h"
#include "pe/util/Hooks.h"
#include "rc/util/SceneObjUtil.h"

namespace {

class PlayerDisasterTimerUpdate : public pe::OutPacket {
    struct {
        int mFramesOfProsperityTransition;
        int mFramesOfProsperity;
        int mFramesOfAnticipationTransition;
        int mFramesOfAnticipation;
        int mFramesOfDisasterTransition;
        int mFramesOfDisaster;
        int unk1;
        int mFramesSinceLastEvent;
        uintptr_t currentNerveOffset;
    } mData;

public:
    PlayerDisasterTimerUpdate(
        int framesOfProsperityTransition,
        int framesOfProsperity,
        int framesOfAnticipationTransition,
        int framesOfAnticipation,
        int framesOfDisasterTransition,
        int framesOfDisaster,
        int unk1,
        int framesSinceLastEvent,
        const al::Nerve* currentNerve)
        : pe::OutPacket(5)
    {
        mData.mFramesOfProsperityTransition = framesOfProsperityTransition;
        mData.mFramesOfProsperity = framesOfProsperity;
        mData.mFramesOfAnticipationTransition = framesOfAnticipationTransition;
        mData.mFramesOfAnticipation = framesOfAnticipation;
        mData.mFramesOfDisasterTransition = framesOfDisasterTransition;
        mData.mFramesOfDisaster = framesOfDisaster;
        mData.unk1 = unk1;
        mData.mFramesSinceLastEvent = framesSinceLastEvent;
        mData.currentNerveOffset = (uintptr_t)currentNerve - exl::util::modules::GetTargetStart();
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

void sendDisasterModeControllerUpdatePacket(DisasterModeController* controller)
{
    PlayerDisasterTimerUpdate packet(
        controller->mFramesOfProsperityTransition,
        controller->mFramesOfProsperity,
        controller->mFramesOfAnticipationTransition,
        controller->mFramesOfAnticipation,
        controller->mFramesOfDisasterTransition,
        controller->mFramesOfDisaster,
        controller->unk1,
        controller->mFramesSinceLastEvent,
        controller->getNerveKeeper()->getCurrentNerve());
    pe::MPClient::instance().sendPacket(packet);
}

}

HOOK_DEFINE_TRAMPOLINE(SingleModeSceneMovementHook) { static void Callback(SingleModeScene*); };

void SingleModeSceneMovementHook::Callback(SingleModeScene* scene)
{
    PlayerActor* player = static_cast<PlayerActor*>(scene->mLiveActorKit->mPlayerHolder->tryGetPlayer(0));

    DisasterModeController* controller = rc::getDisasterModeController(scene);
    if (controller) {
        if (al::isFirstStep(controller))
            pe::MPClient::instance().log("Nerve: 0x710%x ", ((uintptr_t)al::getCurrentNerve(controller) - exl::util::modules::GetTargetStart()));
    }
    if (al::isPadHoldZR() && al::isPadTriggerPlus()) {
        al::appearItemTiming(player, "ファイアフラワー");
        pe::MPClient::instance().reconnect();
        rc::getGuideGameWindow(scene)->mWindow->appearWithSingleMessage(u"Reconnecting\nBowser cycle kjdsfsdfkjhsdfgkjfsgnm");
        // al::setNerve(controller, pe::util::getNerveAt(0x01318b90));
    }
    if (al::isPadHoldZL() && al::isPadTriggerPlus())
        pe::MPClient::instance().disconnect();
    if (al::isPadHoldZL() && al::isPadHoldZR()) {
    }

    if (controller) {
        controller->mFramesSinceLastEvent = 0;
        RUN_EACH(60, {
            sendDisasterModeControllerUpdatePacket(controller);
        });
        static const al::Nerve* lastNerve = nullptr;
        const al::Nerve* nerve = controller->getNerveKeeper()->getCurrentNerve();
        if (lastNerve != nerve) {
            sendDisasterModeControllerUpdatePacket(controller);
            lastNerve = nerve;
        }
    }

    pe::updatePuppets(scene);

    if (!pe::MPClient::instance().isInited())
        pe::MPClient::instance().connect(pe::MPClient::sServerIp, 7032);
    RUN_EACH(300, pe::MPClient::instance().ping(););

    Orig(scene);
};

void pe::initRCSMultiplayerHooks()
{
    SingleModeSceneMovementHook::InstallAtOffset(0x003e84d0);
}