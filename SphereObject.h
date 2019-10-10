#pragma once
#include "GameObject.h"

class MeshComponent;
class SphereCollider;

class SphereObject : public GameObject
{
public:
	SphereObject();
	~SphereObject();

private:
	MeshComponent* meshComp;
	SphereCollider* sphereCollider;

};

