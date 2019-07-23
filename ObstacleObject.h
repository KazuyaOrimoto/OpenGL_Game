#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;

class ObstacleObject : public GameObject
{
public:
	ObstacleObject(Game* game);
	~ObstacleObject();

private:
	MeshComponent* meshComp;
	BoxCollider* boxCollider;
};

