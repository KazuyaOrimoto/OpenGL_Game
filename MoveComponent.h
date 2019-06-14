#pragma once
#include "Component.h"

class GameObject;

class MoveComponent : public Component
{
public:
	MoveComponent(GameObject* owner, int updateOrder = 10);
	void Update(float deltaTime) override;

};

