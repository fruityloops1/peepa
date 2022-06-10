#pragma once

#include "al/interfaces/IUseHioNode.h"
#include "al/interfaces/IUseNerve.h"
#include "al/nerve/Nerve.h"

namespace al {

    class NerveExecutor : public IUseNerve, public al::HioNode {
      public:
        NerveExecutor(const char*);

        virtual NerveKeeper* getNerveKeeper() const;
        virtual ~NerveExecutor();

        void initNerve(const Nerve*, int);
        void updateNerve();

        al::NerveKeeper* mNerveKeeper;
    };

} // namespace al