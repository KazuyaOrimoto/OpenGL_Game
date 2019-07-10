#pragma once
#include "SceneBase.h"
class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();

	SceneBase* Update(float deltaTime)override;
};

