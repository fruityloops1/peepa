#pragma once

#include "al/LiveActor/LiveActor.h"
#include <sead/prim/seadSafeString.h>

namespace al {

// ActorActionKeeper
void startAction(LiveActor* actor, const char* actionName);
bool tryStartActionIfNotPlaying(LiveActor* actor, const char* actionName);
bool tryStartAction(LiveActor* actor, const char* actionName);

const char* getActionName(const LiveActor* actor);
float getActionFrame(const LiveActor* actor);
bool isActionEnd(const LiveActor* actor);

void setSklAnimFrameRate(LiveActor* actor, float frameRate, int);
float getSklAnimFrameRate(const LiveActor* actor, int);
bool isSklAnimExist(const LiveActor* actor, const char* animName);
bool isSklAnimExist(const LiveActor* actor);
void addPartialSklAnimPartsListRecursive(LiveActor* actor, const char* jointName, int);
void clearSklAnimInterpole(LiveActor* actor);

void bindSklAnimRetargetting(const LiveActor* actor, const SklAnimRetargettingInfo* info); // inlined
void validateSklAnimRetargetting(const LiveActor* actor);
void invalidateSklAnimRetargetting(const LiveActor* actor);

void startHitReaction(const LiveActor* actor, const char* name);
void startHitReactionDisappear(const LiveActor* actor);

void setSklAnimBlendWeightSixfold(LiveActor* actor, float, float, float, float, float, float);

// Clipping
void validateClipping(LiveActor* actor);
void invalidateClipping(LiveActor* actor);

// HitSensorKeeper
al::HitSensor* getHitSensor(const al::LiveActor* actor, const char* sensorName);
al::LiveActor* getSensorHost(const al::HitSensor* sensor);

// Init

void initActor(LiveActor* actor, const ActorInitInfo& info);
void initActorWithArchiveName(LiveActor* actor, const ActorInitInfo& info, const sead::SafeString& archiveName, const char* subArchiveName = nullptr);

void initCreateActorNoPlacementInfo(LiveActor* actor, const ActorInitInfo& info);
void initLinksActor(al::LiveActor* actor, const al::ActorInitInfo& info, const char* linkName, int index);

void initActorAudioKeeper(LiveActor* actor, const ActorInitInfo& info, const char* audioEntryName, const sead::Vector3f* pos3d, const sead::Matrix34f* mtx);
void initActorClipping(LiveActor* actor, const ActorInitInfo& info);
void initActorEffectKeeper(LiveActor* actor, const ActorInitInfo& info, const char* effectEntryName);
void initActorModelKeeper(LiveActor* actor, const ActorInitInfo& info, const char* modelArc, int, const char* animArc);
void initActorSceneInfo(LiveActor* actor, const ActorInitInfo& info);

void initNerve(LiveActor* actor, const Nerve* nerve, int step = 0);
void initJointControllerKeeper(const LiveActor* actor, int);

// Executor
void initExecutorMapObj(LiveActor* actor, const ActorInitInfo& info);
void initExecutorEnemyMovement(LiveActor* actor, const ActorInitInfo& info);
void initExecutorPlayerMovement(LiveActor* actor, const ActorInitInfo& info);

} // namespace al
