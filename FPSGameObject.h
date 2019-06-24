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
	class MoveComponent* mMoveComp;
	class MeshComponent* mMeshComp;
	class FPSCamera* mCameraComp;
	class GameObject* mFPSModel;
	class FPSCameraInput* input;
};

