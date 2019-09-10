#pragma once
#include "SceneBase.h"
class Game;
class PlayScene : public SceneBase
{
public:
	PlayScene(Game* _game);
	~PlayScene();

	SceneBase* Update()override;
};

