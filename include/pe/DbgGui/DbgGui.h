#pragma once

#include "Game/Sequence/ProductSequence.h"
#include "container/seadPtrArray.h"
#include <sead/heap/seadDisposer.h>
#include <sead/heap/seadExpHeap.h>

struct ProductSequenceInitHook;

namespace pe {
namespace gui {

    class IComponent;

    sead::ExpHeap*& getDbgGuiHeap();

    class DbgGui {
        SEAD_SINGLETON_DISPOSER(DbgGui);

        sead::PtrArray<IComponent> mComponents;

        struct {
            ProductSequence* productSequence = nullptr;

            bool showDemoWindow = false;
            bool showHeapViewer = false;
            bool showActorBrowser = false;
        } mSharedData;

    public:
        DbgGui();

        void update();
        void draw();

        friend class IComponent;
        friend ::ProductSequenceInitHook;
    };

} // namespace gui
} // namespace pe
