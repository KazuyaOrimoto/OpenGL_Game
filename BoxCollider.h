#pragma once
#include "ColliderComponent.h"
class BoxCollider : public ColliderComponent
{
public:
	BoxCollider(GameObject* argOwner, int argUpdateOrder = 100, int argCollisionOrder = 100);
	~BoxCollider();

	void OnUpdateWorldTransform() override;

	virtual void OnCollision(const GameObject& argHitObject) override;

	void SetObjectBox(const AABB& argBox) { objectBox = argBox; }
	AABB GetWorldBox() const { return worldBox; }

private:
	//�I�u�W�F�N�g�ɐݒ肷��p�̃{�b�N�X�i���S���I�u�W�F�N�g�̒��S�ɂ���j
	AABB objectBox;
	//�����蔻�肷��Ƃ��Ɏg���{�b�N�X�i���S�����[���h���W�̒��S�ɂ���j
	AABB worldBox;
};

