#pragma once
#include "GameObject.h"

class MoveComponent;
class FollowCamera;
class MeshComponent;
class SphereCollider;

class PlayerObject : public GameObject
{
public:
	PlayerObject(Game* game);
	~PlayerObject();

    void SetVisible(bool visible);

private:

    MoveComponent* moveComp;
    FollowCamera* cameraComp;
    MeshComponent* meshComp;
    SphereCollider* sphereCollider;
};

