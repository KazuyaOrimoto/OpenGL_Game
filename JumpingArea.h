#pragma once
#include "GameObject.h"

class BoxCollider;
class MeshComponent;
struct AABB;

class JumpingArea :
	public GameObject
{
public:
	JumpingArea();
	~JumpingArea();
	void SetBoxCollider(AABB _box);
	virtual void OnCollision(const GameObject& _hitObject) override;

private:
	MeshComponent* meshComp;
	BoxCollider* boxCollider;
};

