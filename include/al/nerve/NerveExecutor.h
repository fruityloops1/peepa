#pragma once

#include "al/interfaces/IUseHioNode.h"
#include "al/interfaces/IUseNerve.h"
#include "al/nerve/Nerve.h"

namespace al {

class NerveExecutor : public IUseNerve, public HioNode {
    al::NerveKeeper* mNerveKeeper = nullptr;

public:
    NerveExecutor(const char* name);

    virtual NerveKeeper* getNerveKeeper() const;
    virtual ~NerveExecutor() = default;

    void initNerve(const Nerve*, int step = 0);
    void updateNerve();
};

} // namespace al