#pragma once
#include "GameObject.h"
class GameClearLogo :
	public GameObject
{
public:
	GameClearLogo();
	~GameClearLogo();

	virtual void GameObjectInput(const InputState & _state) override;
};

