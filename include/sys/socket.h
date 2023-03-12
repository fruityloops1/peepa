#pragma once

#include "types.h"

struct in_addr {
    u32 data; // 0
};

struct sockaddr {
    u8 _0; // 0
    u8 family; // 1
    u16 port; // 2
    in_addr address; // 4
    u8 _8[8]; // 8
};

using sockaddr_in = sockaddr;
