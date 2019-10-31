#pragma once
#include "AnimationController.h"

class BikeObject;

class PlayerAnimationController :
	public AnimationController
{
public:
	PlayerAnimationController(GameObject* _owner,AnimationComponent* _animationComp);
	~PlayerAnimationController();

	void Jump();

private:
	BikeObject* bike;
};

