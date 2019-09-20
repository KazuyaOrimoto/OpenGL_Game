#include "BoxCollider.h"
#include "Math.h"
#include "GameObject.h"
#include "Collision.h"
#include "Game.h"
#include "PhysicsWorld.h"

BoxCollider::BoxCollider(GameObject* _owner, int _updateOrder, int _collisionOrder)
	: ColliderComponent(_owner, _updateOrder, _collisionOrder)
	, objectBox({Vector3::Zero,Vector3::Zero})
	, worldBox({ Vector3::Zero,Vector3::Zero})
{
	PHYSICS->AddBox(this);
}

BoxCollider::~BoxCollider()
{
	PHYSICS->RemoveBox(this);
}

void BoxCollider::OnUpdateWorldTransform()
{
    worldBox.min = (objectBox.min * owner->GetScale()) + owner->GetPosition();
    worldBox.max = (objectBox.max * owner->GetScale()) + owner->GetPosition();
}

