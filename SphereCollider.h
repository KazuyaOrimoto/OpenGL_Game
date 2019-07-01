#pragma once
#include "ColliderComponent.h"


class SphereCollider :
	public ColliderComponent
{
public:
	SphereCollider(GameObject* argOwner, int argUpdateOrder = 100, int argCollisionOrder = 100);
	~SphereCollider();
	
	void OnUpdateWorldTransform() override;

	virtual void OnCollision(const GameObject& argHitObject) override;

	void SetObjectSphere(const Sphere& argSphere) { objectSphere = argSphere; }
	Sphere GetWorldSphere() const { return worldSphere; }

private:
	//�I�u�W�F�N�g�ɐݒ肷��p�̋��i���̒��S���I�u�W�F�N�g�̒��S�ɂ���j
	Sphere objectSphere;
	//�����蔻�肷��Ƃ��Ɏg�����i���̒��S�����[���h���W�̒��S�ɂ���j
	Sphere worldSphere;

};

