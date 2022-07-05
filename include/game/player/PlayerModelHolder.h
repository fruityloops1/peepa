#pragma once

#include "game/player/PlayerModel.h"
#include "types.h"
#include <sead/container/seadPtrArray.h>

class PlayerModelHolder {
    u8 inherit[0x18];

public:
    sead::PtrArray<PlayerModel> mModels;
    int mCurModelIndex = 0;

private:
    u8 unk[0x28];
    int mBufferSize = 0;
    u8 unk1;

public:
    PlayerModelHolder(int allocBuffer);

    virtual void change(int index);
    virtual void show();
    virtual void hide();
    virtual bool isHidden() const;
    virtual void showSilhouette();
    virtual void hideSilhouette();
    virtual bool isSilhouetteHidden() const;
    virtual void showShadow();
    virtual void hideShadow();
    virtual bool isShadowHidden() const;
    virtual void validateMash();
    virtual void invalidateMash();
    virtual bool isMash() const;

    void validateTailDynamics();

    void registerModel(int index, PlayerModel* model);
    void initCurrentModel(int index);
};