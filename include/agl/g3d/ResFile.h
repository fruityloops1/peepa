#pragma once

#include "nn/g3d/ResFile.h"

namespace agl {
namespace g3d {

    class ResFile {
    public:
        void Setup(nn::g3d::ResFile*);
        void BindTexture(nn::g3d::ResFile*, const nn::g3d::ResFile*);
    };

} // namespace g3d
} // namespace agl
