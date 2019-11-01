#pragma once
#include "AnimationClip.h"
#include "Math.h"

class GameObject;
class MainCamera;

class JumpAnimation4 :
	public AnimationClip
{
public:
	JumpAnimation4(GameObject* _gameObject, MainCamera* _camera);
	~JumpAnimation4();

	virtual void Update(float deltaTime);
private:
	float rad;
	Vector3 right;
	MainCamera* camera;
};

