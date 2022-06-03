#pragma once

#include "common.hpp"

#define EXL_MODULE_NAME "Peepa"
#define EXL_MODULE_NAME_LEN (sizeof(EXL_MODULE_NAME) - 1)

#define EXL_DEBUG

/*
#define EXL_USE_FAKEHEAP
#define EXL_SUPPORTS_REBOOTPAYLOAD
*/

namespace exl::setting {
    /* How large the fake .bss heap will be. */
    constexpr size_t HeapSize = 0x5000;
} // namespace exl::setting