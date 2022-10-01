#pragma once

#include "al/interfaces/IUseSceneObjHolder.h"
#include "al/scene/ISceneObj.h"
#include "al/util/SceneObjUtil.h"
#include "game/actors/DisasterModeController.h"
#include "game/actors/KoopaJr.h"
#include "game/layouts/GuideGameWindow.h"
#include "game/player/PlayerRetargettingSelectorSceneObj.h"

namespace rc {

enum class SceneObjType : int {
    PlayerRetargettingSelectorSceneObj = 25,
    GuideGameWindow = 28,
    KoopaJr = 56,
    DisasterModeController = 58
};

inline PlayerRetargettingSelectorSceneObj* getPlayerRetargettingSelector(al::IUseSceneObjHolder* holder) { return static_cast<PlayerRetargettingSelectorSceneObj*>(al::getSceneObj(holder, (int)SceneObjType::PlayerRetargettingSelectorSceneObj)); }
inline GuideGameWindow* getGuideGameWindow(al::IUseSceneObjHolder* holder) { return static_cast<GuideGameWindow*>(al::getSceneObj(holder, (int)SceneObjType::GuideGameWindow)); }
inline KoopaJr* getKoopaJr(al::IUseSceneObjHolder* holder) { return static_cast<KoopaJr*>(al::getSceneObj(holder, (int)SceneObjType::KoopaJr)); }
DisasterModeController* getDisasterModeController(al::IUseSceneObjHolder* holder);

} // namespace rc