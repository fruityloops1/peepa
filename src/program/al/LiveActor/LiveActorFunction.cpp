#include "al/LiveActor/LiveActorFunction.h"

namespace al {

void bindSklAnimRetargetting(const LiveActor* actor, const SklAnimRetargettingInfo* info)
{
    actor->mModelKeeper->mModelCafe->mAnimPlayerSkl->mRetargettingInfo = info;
}

} // namespace al