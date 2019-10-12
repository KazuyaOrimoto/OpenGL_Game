#pragma once
#include "GameObject.h"

class MeshComponent;

class ActionArea : public GameObject
{
public:
	ActionArea(GameObject* _owner);
	~ActionArea();

	void UpdateGameObject(float _deltaTime) override;

private:
	MeshComponent* meshComp;
	GameObject* owner;
};

