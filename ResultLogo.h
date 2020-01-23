#pragma once
#include "GameObject.h"
class ResultLogo :
	public GameObject
{
public:
	ResultLogo();
	~ResultLogo();

	virtual void GameObjectInput(const InputState & _state) override;
};

