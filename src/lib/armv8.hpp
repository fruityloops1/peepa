#pragma once

#include "armv8/register.hpp"
#include "asm.hpp"
#include "common.hpp"

namespace exl::armv8 {

    using InstType = uint;

    template <InstType... Args>
    using InstMask = asml::Mask<InstType, Args...>;

    using InstBitSet = asml::BitSet<InstType>;
} // namespace exl::armv8

/* Needed for endianness. */
namespace exl::asml {
    // template<>
    // constexpr inline armv8::InstType armv8::InstBitSet::Value() const { return m_Data; }
}

#include "armv8/instructions.hpp"