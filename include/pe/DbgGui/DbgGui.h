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
            bool showHacks = false;
            bool showRCSCamera = false;
        } mSharedData;

        bool mIsSingleModeScene = false;

    public:
        DbgGui();

        void update();
        void draw();

        bool isSingleModeScene() const { return mIsSingleModeScene; }

        friend class IComponent;
        friend ::ProductSequenceInitHook;
    };

} // namespace gui
} // namespace pe
