#pragma once
#include "GameObject.h"

class MeshComponent;
class SphereCollider;

class SphereObject : public GameObject
{
public:
	SphereObject(Game* _game);
	~SphereObject();

private:
	MeshComponent* meshComp;
	SphereCollider* sphereCollider;

};

