#pragma once
#include "AnimationClip.h"
#include "Math.h"
class GameObject;


class JumpAnimation :
	public AnimationClip
{
public:
	JumpAnimation(GameObject* _gameObject);
	~JumpAnimation();

	virtual void Update(float deltaTime);

private:
	float rad;
	Vector3 right;

};

