#pragma once
#include "SceneBase.h"
class Game;
class TitleScene :
    public SceneBase
{
public:
    TitleScene(Game* game);
    ~TitleScene();
    SceneBase* Update()override;

};

