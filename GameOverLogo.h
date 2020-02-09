#pragma once
#include "GameObject.h"
class GameOverLogo :
	public GameObject
{
public:
	GameOverLogo();
	~GameOverLogo();

	virtual void GameObjectInput(const InputState & _state) override;
};

