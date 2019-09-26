#include "SphereCollider.h"
#include "Math.h"
#include "GameObject.h"
#include "Collision.h"
#include "Game.h"
#include "PhysicsWorld.h"

SphereCollider::SphereCollider(GameObject* _owner, int _updateOrder, int _collisionOrder)
	: ColliderComponent(_owner, _updateOrder, _collisionOrder)
	, objectSphere({ Vector3::Zero,0.0f })
	, worldSphere ({ Vector3::Zero,0.0f })
{
	PHYSICS->AddSphere(this);
}


SphereCollider::~SphereCollider()
{
	PHYSICS->RemoveSphere(this);
}

void SphereCollider::OnUpdateWorldTransform()
{
	//���[���h���W�ł̒��S�ʒu���X�V����
	worldSphere.center = objectSphere.center + owner->GetPosition();
	//���[���h��Ԃł̋��̑傫�����X�V����
	worldSphere.radius = objectSphere.radius * owner->GetScale();

}

void SphereCollider::CollisionPause()
{
	PHYSICS->RemoveSphere(this);
}

void SphereCollider::CollisionActive()
{
	PHYSICS->AddSphere(this);
}

