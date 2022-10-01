#pragma once

#include "al/interfaces/IUseLayout.h"
#include "al/interfaces/IUseLayoutAction.h"
#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"

namespace al {

void initLayoutActor(LayoutActor*, const LayoutInitInfo&, const char* archiveName, const char*);

void startAction(al::IUseLayoutAction*, const char* actionName, const char* = nullptr);
bool isActionEnd(const al::IUseLayoutAction*, const char* actionName = nullptr);

void setPaneString(IUseLayout*, const char* paneName, const char16_t* text, u16 = 0, int = 0);

} // namespace al