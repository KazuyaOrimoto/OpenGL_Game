#pragma once

#include "GameObject.h"

class Game;

class FPSGameObject : public GameObject
{
public:
	FPSGameObject(Game* game);

	void UpdateGameObject(float deltaTime) override;

	void SetVisible(bool visible);
private:
	class MoveComponent* moveComponent;
	class MeshComponent* mMeshComp;
	class FPSCamera* fpsCamera;
	class GameObject* mFPSModel;
	class FPSCameraInput* input;
};

