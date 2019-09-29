#pragma once

#include "ColliderComponent.h"
#include "PhysicsWorld.h"

class SphereCollider :
	public ColliderComponent
{
public:
	SphereCollider(GameObject* _owner, onCollisionFunc _func, int _updateOrder = 100, int _collisionOrder = 100);
	~SphereCollider();
	
	void OnUpdateWorldTransform() override;

	void SetObjectSphere(const Sphere& _sphere) { objectSphere = _sphere; }
	Sphere GetWorldSphere() const { return worldSphere; }

	virtual void CollisionPause() override;
	virtual void CollisionActive() override;

private:
	//�I�u�W�F�N�g�ɐݒ肷��p�̋��i���S���I�u�W�F�N�g�̒��S�ɂ���j
	Sphere objectSphere;
	//�����蔻�肷��Ƃ��Ɏg�����i���S�����[���h���W�̒��S�ɂ���j
	Sphere worldSphere;

};

