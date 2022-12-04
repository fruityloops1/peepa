#pragma once

#include <sead/math/seadMathNumbers.h>
#include <sead/math/seadQuat.h>
#include <sead/math/seadVector.h>

namespace pe {

template <typename T>
struct Constants {
    Constants() = delete;

    constexpr static T degreesToRadians = sead::numbers::pi_v<T> / 180;
    constexpr static T radiansToDegrees = 180 / sead::numbers::pi_v<T>;
};

sead::Vector3f quatToRotate(const sead::Quatf& quat);

} // namespace pe