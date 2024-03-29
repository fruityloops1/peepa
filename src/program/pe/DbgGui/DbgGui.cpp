#include "al/Controller/ControllerUtil.h"
#include "imgui.h"
#include "pe/DbgGui/DbgGui.h"
#include "pe/DbgGui/MenuBar.h"
#include "pe/DbgGui/Windows/ActorBrowser.h"
#include "pe/DbgGui/Windows/Hacks.h"
#include "pe/DbgGui/Windows/HeapViewer.h"
#include "pe/DbgGui/Windows/ImGuiDemo.h"
#include "pe/DbgGui/Windows/RCSCamera.h"
#include "program/imgui_nvn.h"
#include "util/modules.hpp"

namespace pe {
namespace gui {

    SEAD_SINGLETON_DISPOSER_IMPL(DbgGui)

    sead::ExpHeap*& getDbgGuiHeap()
    {
        static sead::ExpHeap* heap { nullptr };
        return heap;
    }

    DbgGui::DbgGui()
    {
        mComponents.allocBuffer(16, nullptr);
        mComponents.pushBack(new MenuBar);
        mComponents.pushBack(new ImGuiDemo);
        mComponents.pushBack(new HeapViewer);
        mComponents.pushBack(new ActorBrowser);
        mComponents.pushBack(new RCSCamera);
        mComponents.pushBack(new Hacks);
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
