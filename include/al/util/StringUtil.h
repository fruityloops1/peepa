#pragma once

#include <sead/basis/seadTypes.h>
#include <sead/prim/seadSafeString.h>

namespace al {

template <s32 L>
class StringTmp : public sead::FixedSafeString<L> {
public:
    StringTmp(const char* format, ...)
        : sead::FixedSafeString<L>()
    {
        std::va_list args;
        va_start(args, format);
        this->formatV(format, args);
        va_end(args);
    }
    ~StringTmp() = default;
};

bool isEqualString(const char* s1, const char* s2);
bool isEqualString(const sead::SafeString& s1, const sead::SafeString& s2);
bool isEqualSubString(const char* s1, const char* s2);

} // namespace al