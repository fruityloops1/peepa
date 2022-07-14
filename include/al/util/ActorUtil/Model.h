#pragma once

#include "al/actor/LiveActor.h"

namespace al {

void setSklAnimBlendWeightSixfold(LiveActor* actor, float, float, float, float, float, float);

void killPrePassLightAll(const al::LiveActor* actor, int);
void appearPrePassLight(const al::LiveActor* actor, const char*, int);

void calcJointPos(sead::Vector3f* out, const LiveActor* actor, const char* jointName);

} // namespace