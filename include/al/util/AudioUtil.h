#pragma once

#include "al/audio/MeInfo.h"
#include "al/interfaces/IUseAudioKeeper.h"
#include "prim/seadSafeString.h"

namespace al {

void startBgm(const al::IUseAudioKeeper*, const char* name, int, int);
void startSe(const al::IUseAudioKeeper*, const sead::SafeString& name, al::MeInfo*);

} // namespace al