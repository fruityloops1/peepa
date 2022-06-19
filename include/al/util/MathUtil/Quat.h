#pragma once

#include <sead/math/seadQuat.h>

namespace al {

void rotateQuatXDirDegree(sead::Quatf* out, const sead::Quatf& from, float degree);
void rotateQuatYDirDegree(sead::Quatf* out, const sead::Quatf& from, float degree);
void rotateQuatZDirDegree(sead::Quatf* out, const sead::Quatf& from, float degree);

} // namespace al