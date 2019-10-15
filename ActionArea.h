#pragma once
#include "GameObject.h"

class MeshComponent;

class ActionArea : public GameObject
{
public:
	ActionArea(GameObject* _owner);
	~ActionArea();

	void UpdateGameObject(float _deltaTime) override;

	void CanJump();
	void CanNotJump();

private:
	MeshComponent* meshComp;
	MeshComponent* meshComp2;

	GameObject* owner;
};

