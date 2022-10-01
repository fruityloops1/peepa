#pragma once

#include "../armv8.hpp"
#include "stream_patcher.hpp"

namespace exl::patch {

namespace inst = armv8::inst;

class CodePatcher : public StreamPatcher {
private:
    using InstBitSet = armv8::InstBitSet;

public:
    inline CodePatcher(uintptr_t start)
        : StreamPatcher(start)
    {
    }

    inline CodePatcher& WriteInst(InstBitSet inst)
    {
        Write<InstBitSet>(inst);
        return *this;
    }

    /* Special case branches as they are relative to the current position. */
    inline CodePatcher& BranchInstRel(ptrdiff_t address)
    {
        WriteInst(inst::Branch(address));
        return *this;
    }
    inline CodePatcher& BranchLinkInstRel(ptrdiff_t address)
    {
        WriteInst(inst::BranchLink(address));
        return *this;
    }

    /* Address relative to the base (Ro). */
    inline CodePatcher& BranchInst(uintptr_t address)
    {
        BranchInstRel(RelativeAddressFromBase(address));
        return *this;
    }
    inline CodePatcher& BranchLinkInst(uintptr_t address)
    {
        BranchLinkInstRel(RelativeAddressFromBase(address));
        return *this;
    }
    /* Absolute addresses. */
    inline CodePatcher& BranchInst(void* ptr)
    {
        BranchInstRel(RelativeAddressFromPointer(ptr));
        return *this;
    }
    inline CodePatcher& BranchLinkInst(void* ptr)
    {
        BranchLinkInstRel(RelativeAddressFromPointer(ptr));
        return *this;
    }
};
}