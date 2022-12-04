#include "pe/Util/Math.h"

namespace pe {

sead::Vector3f quatToRotate(const sead::Quatf& quat)
{
    sead::Vector3f rotate;
    quat.calcRPY(rotate);
    rotate *= Constants<float>::radiansToDegrees;
    return rotate;
}

} // namespace pe