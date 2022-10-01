#pragma once

#include "al/sequence/Sequence.h"
#include "game/sequence/state/ProductStateSingleMode.h"

class IUseUnknownSequence {
    virtual void unknown(const char*);
};

class ProductSequence : public al::Sequence, IUseUnknownSequence {
    void* unk1;
    class GameDataHolder* mGameDataHolder;
    void* unk2[3];
    class ProductStateBoot* mStateBoot;
    class ProductStateTitle* mStateTitle;
    class ProductStateSingleModeOpening* mStateSingleModeOpening;
    ProductStateSingleMode* mStateSingleMode;
    class ProductStateSingleModeEnding* mStateSingleModeEnding;
    class ProductStateCourseSelect* mStateCourseSelect;
    class ProductStateNetworkStop* mStateNetworkStop;
    class ProductStateStage* mStateStage;
    class ProductStateEnding* mStateEnding;
    class ProductStateAfterEndingEvent* mStateAfterEndingEvent;
    class ProductStateTopMenu* mStateTopMenu;
    class ProductStateTopLuigiBros* mStateTopLuigiBros;

public:
    ~ProductSequence() override;
    void init(const al::SequenceInitInfo& info) override;
    void update() override;
    void drawMain() override;
    void drawSub() override;
    bool isDisposable() const override;
    al::Scene* getCurrentScene() const override;
    void unknown(const char*) override;
};