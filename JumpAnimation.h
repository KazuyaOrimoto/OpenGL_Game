#pragma once
#include "AnimationClip.h"
#include "Math.h"
class GameObject;
class MainCamera;

class JumpAnimation :
	public AnimationClip
{
public:
	JumpAnimation(GameObject* _gameObject, MainCamera* _camera);
	~JumpAnimation();

	virtual void Update(float deltaTime);

private:
	float rad;
	Vector3 right;
	MainCamera* camera;
};

