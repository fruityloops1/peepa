#pragma once

#include "al/actor/LiveActor.h"

namespace al {

    void initActorPoseTFGSV(LiveActor* actor);
    void initActorPoseTFSV(LiveActor* actor);
    void initActorPoseTQSV(LiveActor* actor);
    void initActorPoseTRMSV(LiveActor* actor);
    void initActorPoseTRSV(LiveActor* actor);

    const sead::Vector3f& getTrans(const LiveActor* actor);
    const sead::Vector3f& getRotate(const LiveActor* actor);
    const sead::Vector3f& getScale(const LiveActor* actor);
    const sead::Vector3f& getVelocity(const LiveActor* actor);
    const sead::Vector3f& getFront(const LiveActor* actor);
    const sead::Quatf& getQuat(const LiveActor* actor);
    const sead::Vector3f& getGravity(const LiveActor* actor);

    sead::Vector3f* getTransPtr(LiveActor* actor);
    sead::Vector3f* getRotatePtr(LiveActor* actor);
    sead::Vector3f* getScalePtr(LiveActor* actor);
    sead::Vector3f* getVelocityPtr(LiveActor* actor);
    sead::Vector3f* getFrontPtr(LiveActor* actor);
    sead::Quatf* getQuatPtr(LiveActor* actor);
    sead::Vector3f* getGravityPtr(LiveActor* actor);

    void setTrans(LiveActor* actor, const sead::Vector3f& trans);
    void setTrans(LiveActor* actor, float x, float y, float z);
    void setTransX(LiveActor* actor, float x);
    void setTransY(LiveActor* actor, float y);
    void setTransZ(LiveActor* actor, float z);

    void setRotate(LiveActor* actor, const sead::Vector3f& rotate);
    void setRotateX(LiveActor* actor, float x);
    void setRotateY(LiveActor* actor, float y);
    void setRotateZ(LiveActor* actor, float z);

    void setScale(LiveActor* actor, const sead::Vector3f& scale);
    void setScale(LiveActor* actor, float x, float y, float z);
    void setScale(LiveActor* actor, float scale);
    // ?
    void setScaleY(LiveActor* actor, float y);
    void setScaleZ(LiveActor* actor, float z);

    void setVelocity(LiveActor* actor, const sead::Vector3f& velocity);
    void setVelocity(LiveActor* actor, float x, float y, float z);
    void setVelocityX(LiveActor* actor, float x);
    void setVelocityY(LiveActor* actor, float y);
    // ???
    void setVelocityZero(LiveActor* actor);
    void setVelocityJump(LiveActor* actor, float);
    void setVelocityToDirection(LiveActor* actor, const sead::Vector3f&, float);
    void setVelocityToGravity(LiveActor* actor, float gravity);

    void setFront(LiveActor* actor, const sead::Vector3f& front);

    void setQuat(LiveActor* actor, const sead::Quatf& quat);
    void setGravity(LiveActor* actor, const sead::Vector3f& gravity);

} // namespace al