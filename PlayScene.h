#pragma once
#include "SceneBase.h"
class Game;
class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();

	SceneBase* Update()override;
};

