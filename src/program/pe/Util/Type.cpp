#include "pe/Util/Type.h"
#include "Game/Player/CourseSelectPlayerActor.h"
#include "Game/Player/PlayerActor.h"

namespace pe {
namespace util {

    template <>
    bool checkTypeByVtable<PlayerActor>(const al::LiveActor* actor)
    {
        return getVftOffsetMain(actor) == 0x0137a038;
    }

    template <>
    bool checkTypeByVtable<CourseSelectPlayerActor>(const al::LiveActor* actor)
    {
        return getVftOffsetMain(actor) == 0x0128a7d0;
    }

    PlayerActor* checkPlayer(al::LiveActor* instance)
    {
        if (pe::util::checkTypeByVtable<PlayerActor>(instance) or pe::util::checkTypeByVtable<CourseSelectPlayerActor>(instance))
            return static_cast<PlayerActor*>(instance);

        return nullptr;
    }

} // namespace util
} // namespace pe
