#pragma once

#include "al/Model/SklAnimRetargettingInfo.h"
#include <sead/basis/seadTypes.h>

namespace al {

class AnimPlayerSkl {
    u8 unk[0x80];

public:
    const SklAnimRetargettingInfo* mRetargettingInfo;
};

} // namespace al