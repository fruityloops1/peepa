#pragma once

#include <cstddef>
#include <sead/basis/seadTypes.h>

namespace pe {

class OutPacket {
public:
    const u8 mId = -1;

    OutPacket() = delete;
    OutPacket(u8 id)
        : mId(id)
    {
    }

    virtual size_t calcSize() { return 0; };
    virtual void construct(u8* out) {};
};

} // namespace fl