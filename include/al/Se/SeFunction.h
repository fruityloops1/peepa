#pragma once

#include "al/Audio/AudioKeeper.h"
#include "al/Audio/MeInfo.h"
#include <sead/prim/seadSafeString.h>

namespace al {

void startSe(const IUseAudioKeeper*, const sead::SafeString& name, MeInfo*);
void setSeSeqLocalVariableDefault(const IUseAudioKeeper*, int, int);

} // namespace al
