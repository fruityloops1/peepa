#pragma once

#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"

namespace al {

    void initLayoutActor(LayoutActor*, const LayoutInitInfo&, const char* archiveName, const char*);

} // namespace al