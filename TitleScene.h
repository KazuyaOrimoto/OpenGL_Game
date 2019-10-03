#pragma once
#include "SceneBase.h"
class Game;
class TitleScene :
    public SceneBase
{
public:
    TitleScene();
    ~TitleScene();
    SceneBase* Update()override;

};

