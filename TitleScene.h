#pragma once
#include "SceneBase.h"
class Game;
class TitleScene :
    public SceneBase
{
public:
    TitleScene(Game* _game);
    ~TitleScene();
    SceneBase* Update()override;

};

