#pragma once

#include "GameObject.h"

class Ship : public GameObject
{
public:
	Ship(Game* game);
	~Ship();

	void UpdateGameObject(float argDeltaTime) override;

private:
};

