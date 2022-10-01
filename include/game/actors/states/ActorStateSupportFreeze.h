#pragma once

#include "al/nerve/ActorStateBase.h"
#include "al/sensor/HitSensor.h"
#include "al/sensor/ScreenPointTarget.h"
#include "al/sensor/ScreenPointer.h"
#include "al/sensor/SensorMsg.h"

class ActorStateSupportFreezeParam {
    u8 unk[0x1c];

public:
    ActorStateSupportFreezeParam();
};

class ActorStateSupportFreeze : public al::ActorStateBase {
    void* unk;
    class AnimScaleController* mAnimScaleController = nullptr;
    u8 unk2[0x20];
    ActorStateSupportFreezeParam* mStateParam = nullptr;

public:
    ActorStateSupportFreeze(al::LiveActor* parent, const ActorStateSupportFreezeParam* param);

    void appear() override;
    void kill() override;

    bool receiveMsg(const al::SensorMsg* msg, al::HitSensor*);
    bool receiveMsgScreenPoint(const al::SensorMsg* msg, al::ScreenPointer* pointer, al::ScreenPointTarget* target);

    void exeBind();
};