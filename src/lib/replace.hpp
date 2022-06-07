#include "common.hpp"
#include "hook.hpp"

namespace exl::replace {
    void ReplaceData(uintptr_t target, uintptr_t source, size_t size);

#define MAKE_ASM(name, assembly)                                                                                       \
    asm(".global __asm" #name "\n"                                                                                     \
        "__asm" #name ":\n" assembly);                                                                                 \
    extern const u32 __asm##name[]

#define REPLACE_DATA(target, source, size) exl::replace::ReplaceData((uintptr_t)target, (uintptr_t)source, size)
#define REPLACE_ASM(target, name, length) REPLACE_DATA(target, __asm##name, length * sizeof(u32))
#define REPLACE_ASM_O(offset, name, length) REPLACE_ASM(exl::hook::GetTargetOffset(offset), name, length)
} // namespace exl::replace