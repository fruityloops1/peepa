#include "pe/DbgGui/DbgGui.h"
#include "imgui.h"
#include "pe/DbgGui/MenuBar.h"
#include "pe/DbgGui/Windows/ActorBrowser.h"
#include "pe/DbgGui/Windows/HeapViewer.h"
#include "pe/DbgGui/Windows/ImGuiDemo.h"

namespace pe {
namespace gui {

    SEAD_SINGLETON_DISPOSER_IMPL(DbgGui)

    sead::FrameHeap*& getDbgGuiHeap()
    {
        static sead::FrameHeap* heap { nullptr };
        return heap;
    }

    DbgGui::DbgGui()
    {
        mComponents.allocBuffer(16, nullptr);
        mComponents.pushBack(new MenuBar);
        mComponents.pushBack(new ImGuiDemo);
        mComponents.pushBack(new HeapViewer);
        mComponents.pushBack(new ActorBrowser);
    }

    void DbgGui::draw()
    {
        for (IComponent& c : mComponents)
            c.draw();
    }

    void DbgGui::update()
    {
        for (IComponent& c : mComponents)
            c.update();
    }

} // namespace gui
} // namespace pe
