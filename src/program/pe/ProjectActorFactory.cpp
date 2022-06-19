#include "pe/ProjectActorFactory.h"
#include "pe/TestActor.h"

constexpr static al::ActorFactoryTableEntry customActorEntries[] = {
    { "TestActor", pe::createActorFunction<pe::TestActor> }
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