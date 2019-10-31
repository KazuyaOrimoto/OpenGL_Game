#pragma once
#include "AnimationClip.h"
#include "Math.h"

class GameObject;
class MainCamera;
class JumpAnimation2 :
	public AnimationClip
{
public:
	JumpAnimation2(GameObject* _gameObject, MainCamera* _camera);
	~JumpAnimation2();

	virtual void Update(float deltaTime);
private:
	float rad;
	Vector3 right;
	MainCamera* camera;
};
