#include "al/Draw/GraphicsStressDirector.h"
#include "al/Draw/GraphicsSystemInfo.h"
#include "al/LiveActor/LiveActorFunction.h"
#include "al/Nerve/Nerve.h"
#include "al/Scene/LiveActorKit.h"
#include "hook/trampoline.hpp"
#include "imgui.h"
#include "patch/code_patcher.hpp"
#include "pe/DbgGui/Windows/Hacks.h"
#include "pe/Util/Nerve.h"

namespace al {

class DepthOfFieldDrawer;
class LightIntensityDirector;
class GraphicsAreaDirector;

} // namespace al

namespace pe {
namespace gui {

    static bool sIsDisabledStartClipped = false;
    static bool sIsDisabledBloom = false;
    static bool sIsDisabledTransparentWall = false;
    static bool sIsDisabledDynamicResolution = false;
    static bool sIsDisabledDepthOfField = false;

    HOOK_DEFINE_TRAMPOLINE(DisableStartClipped) { static void Callback(al::LiveActor*); };
    HOOK_DEFINE_TRAMPOLINE(DisableStartClippedByLod) { static void Callback(al::LiveActor*); };
    HOOK_DEFINE_TRAMPOLINE(DisableBloom) { static void Callback(al::LightIntensityDirector * lightDirector, al::GraphicsAreaDirector * graphicsDirector, const char* str); };

    void DisableStartClipped::Callback(al::LiveActor* actor)
    {
        if (!sIsDisabledStartClipped)
            Orig(actor);
    }

    void DisableStartClippedByLod::Callback(al::LiveActor* actor)
    {
        if (!sIsDisabledStartClipped)
            Orig(actor);
    }

    void DisableBloom::Callback(al::LightIntensityDirector* lightDirector, al::GraphicsAreaDirector* graphicsDirector, const char* str)
    {
        if (!sIsDisabledBloom)
            Orig(lightDirector, graphicsDirector, str);
    }

    static void disableTransparentWallHook(al::LiveActor* actor)
    {
        if (sIsDisabledTransparentWall)
            actor->kill();
        else
            al::trySyncStageSwitchAppearAndKill(actor);
    }

    static void disableDynamicResolutionHook(al::GraphicsStressDirector* graphics)
    {
        static class : public al::Nerve {
            void execute(al::NerveKeeper*) const override { }
            void executeOnEnd(al::NerveKeeper*) const override { }
        } dummy;

        if (sIsDisabledDynamicResolution)
            graphics->initNerve(&dummy);
        else
            graphics->initNerve(pe::util::getNerveAt(0x013e7c30));
    }

    Hacks::Hacks()
    {
        using Patcher = exl::patch::CodePatcher;

        DisableStartClipped::InstallAtOffset(0x0085c3c0);
        DisableStartClippedByLod::InstallAtOffset(0x0085c6f0);
        // DisableBloom::InstallAtOffset(0x0081f2c0);

        Patcher(0x002d65b4).BranchLinkInst((void*)disableTransparentWallHook);
        Patcher(0x0080196c).BranchLinkInst((void*)disableDynamicResolutionHook);
    }

    void Hacks::update() { }
    void Hacks::draw()
    {
        if (getDbgGuiSharedData().showHacks && ImGui::Begin("Hacks", &getDbgGuiSharedData().showHacks)) {
            ImGui::Checkbox("Disable StartClipped (LAG)", &sIsDisabledStartClipped);
            if (ImGui::Checkbox("Disable Bloom", &sIsDisabledBloom)) {
                if (sIsDisabledBloom)
                    exl::patch::CodePatcher(0x009571d4).Write(exl::armv8::inst::Nop());
                else
                    exl::patch::CodePatcher(0x009571d4).WriteInst(0x97F92B97);
            }
            if (ImGui::Checkbox("Disable DOF", &sIsDisabledDepthOfField)) {
                if (sIsDisabledDepthOfField)
                    exl::patch::CodePatcher(0x0088ef40).Write(exl::armv8::inst::Ret());
                else
                    exl::patch::CodePatcher(0x0088ef40).WriteInst(0x39420008);
            }

            ImGui::Separator();

            ImGui::Checkbox("Disable TransparentWalls", &sIsDisabledTransparentWall);
            ImGui::Checkbox("Disable Dynamic Resolution", &sIsDisabledDynamicResolution);
            ImGui::End();
        }
    }

} // namespace gui
} // namepace pe
