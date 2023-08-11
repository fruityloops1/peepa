#pragma once

#include <cstddef>
#include <cstdio>

namespace pe {

void log(const char* msg);

template <typename... Args>
void log(const char* fmt, Args... args)
{
    size_t size = snprintf(nullptr, 0, fmt, args...);
    char data[size + 1];
    snprintf(data, size, fmt, args...);
    log((const char*)data);
}

} // namespace pe
