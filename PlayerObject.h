#pragma once
#include "GameObject.h"

class MoveComponent;
class MeshComponent;
class MainCamera;
class SphereCollider;
class AutoRunComponent;

class PlayerObject : public GameObject
{
public:
	PlayerObject(Game* game);

	virtual void UpdateGameObject(float argDaltaTime);

    void SetVisible(bool visible);

private:
    MoveComponent* moveComp;
    MeshComponent* meshComp;
    SphereCollider* sphereCollider;
    MainCamera* camera;
    AutoRunComponent* autoRun;
};

