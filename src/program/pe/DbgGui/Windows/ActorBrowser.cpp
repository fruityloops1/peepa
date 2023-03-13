#include "pe/DbgGui/Windows/ActorBrowser.h"
#include "Game/Player/PlayerActor.h"
#include "Game/Sequence/ProductSequence.h"
#include "al/LiveActor/ActorPoseKeeperBase.h"
#include "al/LiveActor/LiveActorFlag.h"
#include "al/LiveActor/SubActorKeeper.h"
#include "al/Nerve/NerveFunction.h"
#include "al/Player/PlayerHolder.h"
#include "heap/seadHeapMgr.h"
#include "imgui.h"
#include "pe/Client/MPClient.h"
#include <sead/heap/seadHeap.h>

namespace pe {
namespace gui {

    void ActorBrowser::update()
    {
    }

    void ActorBrowser::showBrowser(ProductSequence* sequence)
    {
        if (ImGui::Begin("ActorBrowser", &getDbgGuiSharedData().showActorBrowser)) {

            al::Scene* scene = sequence->mCurrentInitScene ? sequence->mCurrentInitScene : sequence->mCurrentScene;
            al::LiveActorKit* kit = scene->mLiveActorKit;
            if (kit) {
                al::LiveActorGroup* allActors = kit->mAllActors;

                char buf[128];
                snprintf(buf, sizeof(buf), "%d/%d (%s)", allActors->mSize, allActors->mCapacity, allActors->mName);
                ImGui::ProgressBar(allActors->mSize / (float(allActors->mCapacity) / 100) / 100, ImVec2(-FLT_MIN, 0), buf);

                // actors with UnitConfigName
                for (int i = 0; i < allActors->mSize; i++) {
                    al::LiveActor* actor(allActors->mActors[i]);
                    showActorInList(actor);
                }

                // non-placement actors at bottom
                for (int i = 0; i < allActors->mSize; i++) {
                    al::LiveActor* actor(allActors->mActors[i]);
                    showActorInListNoUnitConfigName(actor);
                }
            }

            ImGui::End();
        }
    }

    void ActorBrowser::showActorInList(al::LiveActor* actor)
    {
        char buf[128];
        if (actor && actor->getPlacementHolder()->mUnitConfigName) {
            al::PlacementHolder* holder = actor->getPlacementHolder();
            const char* unitConfigName = holder->mUnitConfigName;
            const char* modelName = holder->mModelNameClone;

            if (modelName)
                snprintf(buf, sizeof(buf), "%s (%s)", unitConfigName, modelName);
            else
                strncpy(buf, unitConfigName, sizeof(buf));

            ImGui::PushID(actor);
            if (ImGui::Selectable(buf, mCurrentSelection == actor))
                mCurrentSelection = mCurrentSelection == actor ? nullptr : actor;
            ImGui::PopID();
        }
    }

    void ActorBrowser::showActorInListNoUnitConfigName(al::LiveActor* actor)
    {
        if (actor && !actor->getPlacementHolder()->mUnitConfigName) {
            ImGui::PushID(actor);
            if (ImGui::Selectable(actor->getName(), mCurrentSelection == actor))
                mCurrentSelection = mCurrentSelection == actor ? nullptr : actor;
            ImGui::PopID();
        }
    }

    void ActorBrowser::showActorView()
    {
        if (ImGui::Begin("Actor")) {
            if (mCurrentSelection) {
                const char* actorName = mCurrentSelection->getName();
                const char* unitConfigName = mCurrentSelection->getPlacementHolder()->mUnitConfigName;
                if (!unitConfigName)
                    unitConfigName = "nullptr";
                const char* modelName = mCurrentSelection->getPlacementHolder()->mModelNameClone;
                if (!modelName)
                    modelName = "nullptr";
                const char* objectId = mCurrentSelection->getPlacementHolder()->mIdClone;
                if (!objectId)
                    objectId = "nullptr";

                ImGui::InputText("Actor Name", const_cast<char*>(actorName), 0, ImGuiInputTextFlags_ReadOnly);
                ImGui::InputText("Id", const_cast<char*>(objectId), 0, ImGuiInputTextFlags_ReadOnly);
                ImGui::InputText("UnitConfigName", const_cast<char*>(unitConfigName), 0, ImGuiInputTextFlags_ReadOnly);
                ImGui::InputText("ModelName", const_cast<char*>(modelName), 0, ImGuiInputTextFlags_ReadOnly);

                if (mCurrentSelection->getActorPoseKeeper() && ImGui::CollapsingHeader("Pose"))
                    showActorPoseKeeper();

                if (mCurrentSelection->getNerveKeeper() && ImGui::CollapsingHeader("Nerve"))
                    showNerveKeeper();

                if (mCurrentSelection->getSubActorKeeper() && ImGui::CollapsingHeader("Sub Actors"))
                    showSubActorKeeper();

                if (mCurrentSelection->getLiveActorFlag() && ImGui::CollapsingHeader("Flags"))
                    showLiveActorFlag();

            } else
                ImGui::Text("No Actor Selected!");
            ImGui::End();
        }
    }

    void ActorBrowser::showActorPoseKeeper()
    {
        sead::Vector3f* velocityPtr = al::getScalePtr(mCurrentSelection);

        PlayerActor* player = al::getPlayerActor(mCurrentSelection, 0);

        auto setTransForAllPlayers = [this](const sead::Vector3f& trans) {
            for (int i = 0; i < al::getPlayerNumMax(mCurrentSelection); i++)
                al::getPlayerActor(mCurrentSelection, i)->mPlayer->mPlayerProperty->trans = trans;
        };

        if (player) {
            if (ImGui::Button("Teleport to"))
                setTransForAllPlayers(al::getTrans(mCurrentSelection));

            if (ImGui::Button("Teleport 5m above")) {
                sead::Vector3f trans = al::getTrans(mCurrentSelection);
                trans.y += 500;
                setTransForAllPlayers(trans);
            }
        }

        ImGui::DragFloat3("Trans", al::getTransPtr(mCurrentSelection)->e.data());
        ImGui::DragFloat3("Scale", velocityPtr->e.data());
        for (int i = 0; i < 3; i++)
            if (velocityPtr->e[i] == 0)
                velocityPtr->e[i] = 1; // 0 in scale = crashes game
        ImGui::DragFloat3("Velocity", al::getVelocityPtr(mCurrentSelection)->e.data());
    }

    void ActorBrowser::showNerveKeeper()
    {
        ImGui::Text("Nerve Pointer: 0x%p", al::getCurrentNerve(mCurrentSelection));
        ImGui::Text("Nerve Step: %d", al::getNerveStep(mCurrentSelection));
    }

    void ActorBrowser::showSubActorKeeper()
    {
        al::LiveActor* parent = mCurrentSelection;
        for (int i = 0; i < al::getSubActorNum(parent); i++) {
            al::LiveActor* actor = al::getSubActor(parent, i);
            showActorInListNoUnitConfigName(actor);
        }
    }

    void ActorBrowser::showLiveActorFlag()
    {
        al::LiveActorFlag* flags = mCurrentSelection->getLiveActorFlag();
        ImGui::Checkbox("Dead", &flags->isDead);
        ImGui::Checkbox("Clipped", &flags->isDead);
        ImGui::Checkbox("flag3", &flags->flag3);
        ImGui::Checkbox("Draw", &flags->isDraw);
        ImGui::Checkbox("ClippedByLod", &flags->isClippedByLod);
        ImGui::Checkbox("OffCalcAnim", &flags->isOffCalcAnim);
        ImGui::Checkbox("HideModel", &flags->isHideModel);
        ImGui::Checkbox("ColliderDisabled", &flags->isColliderDisabled);
        ImGui::Checkbox("flag9", &flags->flag9);
        ImGui::Checkbox("flag10", &flags->flag10);
        ImGui::Checkbox("MaterialCode", &flags->isMaterialCode);
        ImGui::Checkbox("AreaTarget", &flags->isAreaTarget);
        ImGui::Checkbox("UpdateMovementEffectAudioCollisionSensor", &flags->isUpdateMovementEffectAudioCollisionSensor);
    }

    void ActorBrowser::draw()
    {
        if (!getDbgGuiSharedData().showActorBrowser)
            return;

        ProductSequence* sequence = getDbgGuiSharedData().productSequence;

        if (sequence && (sequence->mCurrentScene or sequence->mCurrentInitScene)) {
            showBrowser(sequence);
            showActorView();
        } else if (ImGui::Begin("ActorBrowser", &getDbgGuiSharedData().showActorBrowser)) {
            ImGui::Text("No Scene!");
            mCurrentSelection = nullptr;
            ImGui::End();
        }
    }

} // namespace gui
} // namespace pe
