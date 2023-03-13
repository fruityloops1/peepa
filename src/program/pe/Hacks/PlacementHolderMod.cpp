#include "pe/Hacks/PlacementHolderMod.h"
#include "al/LiveActor/LiveActor.h"
#include "al/Placement/PlacementHolder.h"
#include "heap/seadHeapMgr.h"
#include "hook/trampoline.hpp"
#include "lib.hpp"
#include "pe/Client/MPClient.h"
#include "pe/DbgGui/DbgGui.h"
#include <sead/basis/seadNew.h>

PATCH_DEFINE_ASM(PlacementHolderSizeModHook1, "mov w0, #0x40");
PATCH_DEFINE_ASM(PlacementHolderSizeModHook2, "mov w0, #0x40");

static void deletePlacementHolderIfExist(al::LiveActor* actor)
{
    al::PlacementHolder* placementHolder = actor->getPlacementHolder();
    if (placementHolder)
        delete placementHolder;
}

al::PlacementHolder::~PlacementHolder()
{
    pe::MPClient::instance().log("~PlacementHolder()");
    sead::ScopedCurrentHeapSetter setter(pe::gui::getDbgGuiHeap());

    if (mUnitConfigName)
        delete mUnitConfigName;
    if (mIdClone)
        delete mIdClone;
    if (mModelNameClone)
        delete mModelNameClone;
}

HOOK_DEFINE_TRAMPOLINE(LiveActorDtorHook1) { static void Callback(al::LiveActor * actor, void* vtt); }; // vtt dtor
HOOK_DEFINE_TRAMPOLINE(LiveActorDtorHook2) { static void Callback(al::LiveActor * actor); }; // dtor
HOOK_DEFINE_TRAMPOLINE(LiveActorDtorHook3) { static void Callback(al::LiveActor * actor); }; // delete dtor
HOOK_DEFINE_TRAMPOLINE(PlacementHolderCtorHook) { static void Callback(al::PlacementHolder * holder); };
HOOK_DEFINE_TRAMPOLINE(PlacementHolderInitHook) { static void Callback(al::PlacementHolder * holder, const al::PlacementInfo& info); };

void LiveActorDtorHook1::Callback(al::LiveActor* actor, void* vtt)
{
    Orig(actor, vtt);
    deletePlacementHolderIfExist(actor);
}

void LiveActorDtorHook2::Callback(al::LiveActor* actor)
{
    Orig(actor);
    deletePlacementHolderIfExist(actor);
}

void LiveActorDtorHook3::Callback(al::LiveActor* actor)
{
    deletePlacementHolderIfExist(actor);
    Orig(actor);
}

void PlacementHolderCtorHook::Callback(al::PlacementHolder* holder)
{
    Orig(holder);
    holder->mUnitConfigName = nullptr;
    holder->mIdClone = nullptr;
    holder->mModelNameClone = nullptr;
}

void PlacementHolderInitHook::Callback(al::PlacementHolder* holder, const al::PlacementInfo& info)
{
    Orig(holder, info);

    sead::ScopedCurrentHeapSetter setter(pe::gui::getDbgGuiHeap());

    const char* unitConfigName = nullptr;
    if (info.getPlacementIter().tryGetStringByKey(&unitConfigName, "UnitConfigName")) {
        size_t size = strlen(unitConfigName) + 1;
        char* out = new char[size];
        holder->mUnitConfigName = out;
        strncpy(out, unitConfigName, size - 1);
    }

    const char* id = nullptr;
    if (info.getPlacementIter().tryGetStringByKey(&id, "Id")) {
        size_t size = strlen(id) + 1;
        char* out = new char[size];
        holder->mIdClone = out;
        strncpy(out, id, size - 1);
    }

    const char* modelName = nullptr;
    if (info.getPlacementIter().tryGetStringByKey(&modelName, "ModelName")) {
        size_t size = strlen(modelName) + 1;
        char* out = new char[size];
        holder->mModelNameClone = out;
        strncpy(out, modelName, size - 1);
    }
}

namespace pe {

void initPlacementHolderModHooks()
{
    PlacementHolderSizeModHook1::InstallAtOffset(0x0085b4d4);
    PlacementHolderSizeModHook2::InstallAtOffset(0x0085b5ac);
    LiveActorDtorHook1::InstallAtOffset(0x0085b5d0);
    LiveActorDtorHook2::InstallAtOffset(0x0085b680);
    LiveActorDtorHook3::InstallAtOffset(0x0085b720);
    PlacementHolderCtorHook::InstallAtOffset(0x00984150);
    PlacementHolderInitHook::InstallAtOffset(0x00984170);
}

} // namespace pe
