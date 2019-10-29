#pragma once
#include "AnimationController.h"
class PlayerAnimationController :
	public AnimationController
{
public:
	PlayerAnimationController(GameObject* _owner,AnimationComponent* _animationComp);
	~PlayerAnimationController();

	void Jump();
};

