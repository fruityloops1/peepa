#include "pe/factory/ProjectActorFactory.h"
#include "al/util/ActorUtil/Init.h"
#include "pe/actors/CoinVideoPlayer.h"
#include "pe/actors/Foomin.h"
#include "pe/actors/NeedleSwitchParts.h"
#include "pe/actors/PatanPanel.h"
#include "pe/actors/PatanPanelStarter.h"

constexpr static al::ActorFactoryTableEntry customActorEntries[] = {
    { "Foomin", pe::createActorFunction<pe::Foomin> },
    { "NeedleSwitchParts", pe::createActorFunction<pe::NeedleSwitchParts> }
};

pe::ProjectActorFactory::ProjectActorFactory()
{
    static al::ActorFactoryTableEntry
        outEntries[sizeof(customActorEntries) / sizeof(al::ActorFactoryTableEntry) + sizeof(::ProjectActorFactory::sActorEntries) / sizeof(al::ActorFactoryTableEntry)];
    static bool isInitialized = false;

    if (!isInitialized) {
        int i = 0;

        for (const al::ActorFactoryTableEntry& entry : customActorEntries) {
            outEntries[i] = entry;
            i++;
        }

        for (const al::ActorFactoryTableEntry& entry : ::ProjectActorFactory::sActorEntries) {
            outEntries[i] = entry;
            i++;
        }
        isInitialized = true;
    }

    initFactory(outEntries);
}