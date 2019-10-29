#pragma once
#include "AnimationClip.h"

class GameObject;
class JumpAnimation2 :
	public AnimationClip
{
public:
	JumpAnimation2(GameObject* _gameObject);
	~JumpAnimation2();

	virtual void Update(float deltaTime);
};
