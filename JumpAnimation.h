#pragma once
#include "AnimationClip.h"

class GameObject;
class JumpAnimation :
	public AnimationClip
{
public:
	JumpAnimation(GameObject* _gameObject);
	~JumpAnimation();

	virtual void Update(float deltaTime);
};

