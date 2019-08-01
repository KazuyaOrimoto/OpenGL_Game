#pragma once
#include "Component.h"
#include "Collision.h"

class GameObject;

class ColliderComponent : public Component
{
public:
	ColliderComponent(GameObject* argOwner, int argUpdateOrder = 100,int argCollisionOrder = 100);
	virtual ~ColliderComponent();

	int GetCollisionOrder() const { return collisionOrder; }


	//�I�u�W�F�N�g�����ɓ����������ɂ߂肱�݂��炸�炷����
	virtual void ShiftObject(const Sphere& argHirSphere) {}
	//�I�u�W�F�N�g�����ʂɓ����������ɂ߂肱�݂��炸�炷����
	virtual void ShiftObject(const Plane& argHitPlane) {}
	//�I�u�W�F�N�g��AABB�ɓ����������ɂ߂肱�݂��炸�炷����
	virtual void ShiftObject(const AABB& argHitBox) {}
	//�I�u�W�F�N�g���J�v�Z���ɓ����������ɂ߂肱�݂��炸�炷����
	virtual void ShiftObject(const Capsule& argHitCapsule) {}

private:
	bool isTrigger;
	//���l���傫������D�悵�Ă߂荞�݂��瓮��������������i0�ȉ��͓������Ȃ��j
	int collisionOrder;
};

