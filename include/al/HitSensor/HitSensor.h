#pragma once

#include <sead/basis/seadTypes.h>
#include <sead/container/seadPtrArray.h>
#include <sead/math/seadMatrix.h>
#include <sead/math/seadVector.h>

namespace al {

class LiveActor;

class HitSensor {
    const char* const mName = nullptr;
    u8 unk[0x38];
    al::LiveActor* mParentActor;
    const sead::Vector3f* mFollowPos;
    const sead::Matrix34f* mFollowMtx;

public:
    HitSensor(al::LiveActor* parent, const char* name, unsigned int, float, unsigned short, const sead::Vector3f*, const sead::Matrix34f*, const sead::Vector3f&);

    bool trySensorSort();
    void setFollowPosPtr(const sead::Vector3<float>*);
    void setFollowMtxPtr(const sead::Matrix34<float>*);
    void validate();
    void invalidate();
    void validateBySystem();
    void invalidateBySystem();
    void update();
    void addHitSensor(al::HitSensor* sensor);

    inline const char* const getName() { return mName; }
};

} // namespace al