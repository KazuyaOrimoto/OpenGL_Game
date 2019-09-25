#pragma once
#include "GameObject.h"

class BoxCollider;
class MeshComponent;
struct AABB;

class JumpingArea :
	public GameObject
{
public:
	JumpingArea(Game* _game);
	~JumpingArea();
	void SetBoxCollider(AABB _box);

private:
	MeshComponent* meshComp;
	BoxCollider* boxCollider;
};

