#include "SphereCollider.h"
#include "Math.h"
#include "GameObject.h"
#include "Collision.h"
#include "Game.h"
#include "PhysicsWorld.h"

SphereCollider::SphereCollider(GameObject* argOwner, int argUpdateOrder, int argCollisionOrder)
	: ColliderComponent(argOwner, argUpdateOrder, argCollisionOrder)
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

void SphereCollider::OnCollision(const GameObject & argHitObject)
{
}
