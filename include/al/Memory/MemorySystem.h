#pragma once

#include <sead/heap/seadHeap.h>
#include <sead/heap/seadHeapMgr.h>

namespace al {

class SceneHeapSetter : sead::ScopedCurrentHeapSetter {
    sead::Heap* _8;

public:
    SceneHeapSetter();
};

void createSceneHeap(const char* stageName);

sead::Heap* getSequenceHeap();

} // namespace al
