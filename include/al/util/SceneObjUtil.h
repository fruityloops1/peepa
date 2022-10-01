#pragma once

#include "al/interfaces/IUseSceneObjHolder.h"
#include "al/scene/ISceneObj.h"

namespace al {

void createSceneObj(IUseSceneObjHolder*, int index);
void setSceneObj(IUseSceneObjHolder*, ISceneObj*, int index);
ISceneObj* getSceneObj(IUseSceneObjHolder*, int index);

} // namespace al