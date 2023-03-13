#include "pe/DbgGui/MenuBar.h"
#include "heap/seadHeapMgr.h"
#include "imgui.h"
#include "pe/Util/Nerve.h"
#include <sead/heap/seadHeap.h>

namespace pe {
namespace gui {

    void MenuBar::update()
    {
    }

    void MenuBar::draw()
    {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("Windows")) {
                ImGui::Checkbox("Demo Window", &getDbgGuiSharedData().showDemoWindow);
                ImGui::Checkbox("HeapViewer", &getDbgGuiSharedData().showHeapViewer);
                ImGui::Checkbox("ActorBrowser", &getDbgGuiSharedData().showActorBrowser);
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

} // namespace gui
} // namespace pe
