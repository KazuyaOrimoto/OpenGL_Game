#pragma once
#include "AnimationClip.h"
#include "Math.h"

class GameObject;
class MainCamera;
class JumpAnimation3 :
	public AnimationClip
{
public:
	JumpAnimation3(GameObject* _gameObject, MainCamera* _camera);
	~JumpAnimation3();

	virtual void Update(float deltaTime);
private:
	float rad;
	Vector3 right;
	MainCamera* camera;
};

