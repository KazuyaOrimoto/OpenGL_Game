#include "BoxCollider.h"
#include "Math.h"
#include "GameObject.h"
#include "Collision.h"
#include "Game.h"
#include "PhysicsWorld.h"


BoxCollider::BoxCollider(GameObject* argOwner, int argUpdateOrder, int argCollisionOrder)
	: ColliderComponent(argOwner, argUpdateOrder, argCollisionOrder)
	, objectBox({Vector3::Zero,Vector3::Zero})
	, worldBox({ Vector3::Zero,Vector3::Zero})
{
	owner->GetGame()->GetPhysicsWorld()->AddBox(this);
}


BoxCollider::~BoxCollider()
{
}

void BoxCollider::OnUpdateWorldTransform()
{
}

void BoxCollider::OnCollision(const GameObject & argHitObject)
{
}
