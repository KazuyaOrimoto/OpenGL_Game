#pragma once

#include "GameObject.h"

class Game;

class FPSGameObject : public GameObject
{
public:
	FPSGameObject(Game* _game);

	void UpdateGameObject(float _deltaTime) override;

	void SetVisible(bool _visible);
private:
	class MoveComponent* moveComponent;
	class MeshComponent* mMeshComp;
	class FPSCamera* fpsCamera;
	class GameObject* mFPSModel;
	class FPSCameraInput* input;
};

