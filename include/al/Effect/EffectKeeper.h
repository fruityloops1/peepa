#pragma once

namespace al {

class EffectKeeper {
};

class IUseEffectKeeper {
    virtual EffectKeeper* getEffectKeeper() const = 0;
};

void tryDeleteEffect(IUseEffectKeeper*, const char* effectName);

} // namespace al