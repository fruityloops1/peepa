#include "pe/Factory/ProjectActorFactory.h"
#include "al/LiveActor/LiveActorFunction.h"
#include "pe/Enemy/Foomin.h"
#include "pe/MapObj/CoinVideoPlayer.h"
#include "pe/MapObj/NeedleSwitchParts.h"
#include "pe/MapObj/PatanPanel.h"
#include "pe/MapObj/PatanPanelStarter.h"

constexpr static al::ActorFactoryTableEntry customActorEntries[] = {
    { "Foomin", pe::createActorFunction<pe::Foomin> },
    { "PatanPanel", pe::createActorFunction<pe::PatanPanel> },
    { "PatanPanelStarter", pe::createActorFunction<pe::PatanPanelStarter> },
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