#pragma once

#include "al/actor/ActorActionKeeper.h"
#include "al/actor/ActorExecuteInfo.h"
#include "al/actor/ActorInitInfo.h"
#include "al/actor/ActorItemKeeper.h"
#include "al/actor/ActorPoseKeeper/ActorPoseKeeperBase.h"
#include "al/actor/ActorSceneInfo.h"
#include "al/actor/ActorScoreKeeper.h"
#include "al/actor/SubActorKeeper.h"
#include "al/area/AreaObjDirector.h"
#include "al/audio/AudioKeeper.h"
#include "al/camera/CameraDirector.h"
#include "al/collision/Collider.h"
#include "al/collision/CollisionDirector.h"
#include "al/collision/CollisionParts.h"
#include "al/effect/EffectKeeper.h"
#include "al/interfaces/IUseAreaObj.h"
#include "al/interfaces/IUseAudioKeeper.h"
#include "al/interfaces/IUseCamera.h"
#include "al/interfaces/IUseCollision.h"
#include "al/interfaces/IUseEffectKeeper.h"
#include "al/interfaces/IUseNerve.h"
#include "al/interfaces/IUseSceneObjHolder.h"
#include "al/interfaces/IUseStageSwitch.h"
#include "al/interfaces/IUseUnknown.h"
#include "al/model/ActorPrePassLightKeeper.h"
#include "al/model/ModelKeeper.h"
#include "al/model/ShadowKeeper.h"
#include "al/rail/RailKeeper.h"
#include "al/scene/SceneObjHolder.h"
#include "al/sensor/HitSensor.h"
#include "al/sensor/HitSensorKeeper.h"
#include "al/sensor/ScreenPointKeeper.h"
#include "al/sensor/ScreenPointTarget.h"
#include "al/sensor/ScreenPointer.h"
#include "al/sensor/SensorMsg.h"
#include "al/stage/StageSwitchKeeper.h"

namespace al {

struct LiveActorFlag {
    bool isDead = true;
    bool isClipped = false;
    bool flag3;
    bool flag4;
    bool flag5;
    bool flag6;
    bool isHideModel = false;
    bool flag8;
    bool flag9;
    bool flag10;
    bool flag11;
    bool flag12;
    bool isUpdateMovementEffectAudioCollisionSensor = true; // true?
};

struct Unknown {
    void* unknown = nullptr;
};

class LiveActor : public IUseNerve,
                  public IUseEffectKeeper,
                  public IUseAudioKeeper,
                  Unknown,
                  public IUseStageSwitch,
                  public IUseSceneObjHolder,
                  public IUseAreaObj,
                  public IUseUnknown,
                  public IUseCamera,
                  public IUseCollision {
protected:
    const char* const mName = nullptr;
    ActorPoseKeeperBase* mActorPoseKeeper = nullptr;
    ActorExecuteInfo* mActorExecuteInfo = nullptr;
    ActorActionKeeper* mActionKeeper = nullptr;
    ActorItemKeeper* mActorItemKeeper = nullptr;
    ActorScoreKeeper* mActorScoreKeeper = nullptr;
    Collider* mCollider = nullptr;
    CollisionParts* mCollisionParts = nullptr;
    ModelKeeper* mModelKeeper = nullptr;
    NerveKeeper* mNerveKeeper = nullptr;
    HitSensorKeeper* mHitSensorKeeper = nullptr;
    ScreenPointKeeper* mScreenPointKeeper = nullptr;
    EffectKeeper* mEffectKeeper = nullptr;
    AudioKeeper* mAudioKeeper = nullptr;
    void* gap = nullptr;
    StageSwitchKeeper* mStageSwitchKeeper = nullptr;
    RailKeeper* mRailKeeper = nullptr;
    ShadowKeeper* mShadowKeeper = nullptr;
    ActorPrePassLightKeeper* mActorPrePassLightKeeper = nullptr;
    SubActorKeeper* mSubActorKeeper = nullptr;
    void* gap3 = nullptr;
    ActorSceneInfo* mActorSceneInfo = nullptr;
    void* gap4 = nullptr;
    LiveActorFlag* mLiveActorFlag = nullptr;
    u8 unk[0x38];

public:
    LiveActor(const char* name);

    NerveKeeper* getNerveKeeper() const override;
    virtual ~LiveActor();
    virtual void init(const ActorInitInfo& info);
    virtual void initAfterPlacement();
    virtual void appear();
    virtual void unk1();
    virtual void unk2();
    virtual void makeActorAppeared();
    virtual void kill();
    virtual void unk3();
    virtual void makeActorDead();
    virtual void unk4();
    virtual void unk5();
    virtual void unk6();
    virtual void unk7();
    virtual void unk8();
    virtual void setTrans(const sead::Vector3f& trans);
    virtual void movement();
    virtual void calcAnim();
    virtual void unk9();
    virtual void unk10();
    virtual void unk11();
    virtual void unk12();
    virtual void unk13();
    virtual void unk14();
    virtual void startClipped();
    virtual void endClipped();
    virtual void unk15();
    virtual void unk16();
    virtual void unk17();
    virtual void unk18();
    virtual void unk19();
    virtual void unk20();
    virtual void unk21();
    virtual bool receiveMsg(const SensorMsg* msg, HitSensor* source, HitSensor* target);
    virtual bool receiveMsgScreenPoint(const SensorMsg* msg, ScreenPointer* pointer, ScreenPointTarget* target);
    virtual void unk22();
    const char* getName() const override;
    virtual const sead::Matrix34f& getBaseMtx();
    EffectKeeper* getEffectKeeper() const override;
    AudioKeeper* getAudioKeeper() const override;
    StageSwitchKeeper* getStageSwitchKeeper() const override;
    SceneObjHolder* getSceneObjHolder() const override;
    CollisionDirector* getCollisionDirector() const override;
    AreaObjDirector* getAreaObjDirector() const override;
    CameraDirector* getCameraDirector() const override;
    void* getUnknown() const override;
    virtual bool isMovePartDisableStaticTouchEffects();
    void initStageSwitchKeeper() override;
    virtual bool unk24();
    virtual void control();
    virtual void unk26();
    virtual void updateCollider();

    void initActionKeeper(const char*, const char*);
    void initActorPrePassLightKeeper(ActorPrePassLightKeeper*);
    void initCollider(float, float, u32);
    void initExecuteInfo(ActorExecuteInfo*);
    void initHitSensor(int sensorAmount);
    void initItemKeeper(int);
    void initModelKeeper(ModelKeeper*);
    void initNerveKeeper(NerveKeeper*);
    void initPoseKeeper(ActorPoseKeeperBase*);
    void initRailKeeper(const ActorInitInfo& info);
    void initSceneInfo(ActorSceneInfo*);
    void initScoreKeeper();
    void initScreenPointKeeper(int targetAmount);
    void initShadowKeeper(ShadowKeeper*);
};

} // namespace al