#include "al/Nerve/NerveExecutor.h"

namespace al {

NerveExecutor::NerveExecutor(const char* name)
{
    // name is ignored
}

NerveKeeper* NerveExecutor::getNerveKeeper() const { return mNerveKeeper; }

} // namespace al