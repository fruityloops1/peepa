#pragma once

namespace al {

class LiveActor;
struct LiveActorFlag {
    bool isDead = true;
    bool isClipped = false;
    bool flag3;
    bool flag4;
    bool flag5;
    bool flag6;
    bool isHideModel = false;
    bool flag8;
    bool flag9;
    bool flag10;
    bool flag11;
    bool flag12;
    bool isUpdateMovementEffectAudioCollisionSensor = true; // true?
};

bool isDead(const LiveActor* actor);
bool isClipped(const LiveActor* actor);

void onCollide(LiveActor* actor);
void offCollide(LiveActor* actor);

} // namespace al
