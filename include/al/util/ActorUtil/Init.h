#pragma once

#include "al/actor/LiveActor.h"
#include "al/nerve/Nerve.h"
#include <sead/prim/seadSafeString.h>

namespace al {

void initActor(LiveActor* actor, const ActorInitInfo& info);
void initActorWithArchiveName(LiveActor* actor, const ActorInitInfo& info, const sead::SafeString& archiveName, const char* subArchiveName = nullptr);

void initCreateActorNoPlacementInfo(LiveActor* actor, const ActorInitInfo& info);
void initLinksActor(al::LiveActor* actor, const al::ActorInitInfo& info, const char* linkName, int index);

void initActorAudioKeeper(LiveActor* actor, const ActorInitInfo& info, const char* audioEntryName);
void initActorClipping(LiveActor* actor, const ActorInitInfo& info);
void initActorEffectKeeper(LiveActor* actor, const ActorInitInfo& info, const char* effectEntryName);
void initActorModelKeeper(LiveActor* actor, const ActorInitInfo& info, const char* modelArc, int, const char* animArc);
void initActorSceneInfo(LiveActor* actor, const ActorInitInfo& info);

void initNerve(LiveActor* actor, const Nerve* nerve, int step = 0);

} // namespace al