#pragma once

#include "al/actor/LiveActor.h"

namespace al {

bool tryStartActionIfNotPlaying(LiveActor* actor, const char*);
void startAction(LiveActor* actor, const char* actionName);
const char* getActionName(const LiveActor* actor);
float getActionFrame(const LiveActor* actor);
bool isActionEnd(const LiveActor* actor);

void setSklAnimFrameRate(LiveActor* actor, float frameRate, int);
float getSklAnimFrameRate(const LiveActor* actor, int);
bool isSklAnimExist(const LiveActor* actor, const char* animName);
bool isSklAnimExist(const LiveActor* actor);
void addPartialSklAnimPartsListRecursive(LiveActor* actor, const char* jointName, int);
void clearSklAnimInterpole(LiveActor* actor);

void startHitReaction(const LiveActor* actor, const char* name);
void startHitReactionDisappear(const LiveActor* actor);

} // namespace al