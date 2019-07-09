#pragma once
#include "Component.h"
class RotateComponent : public Component
{
public:
	RotateComponent(GameObject* argOwner, int argUpdateOrder = 10);

	virtual void Update(float argDeltaTime);

	virtual void ProcessInput(const struct InputState& state);

private:

	bool right;
};

