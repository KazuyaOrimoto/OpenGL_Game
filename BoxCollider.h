#pragma once
#include "ColliderComponent.h"
class BoxCollider : public ColliderComponent
{
public:
	BoxCollider(GameObject* _owner, int _updateOrder = 100, int _collisionOrder = 100);
	~BoxCollider();

	void OnUpdateWorldTransform() override;


	void SetObjectBox(const AABB& _box) { objectBox = _box; }
	AABB GetWorldBox() const { return worldBox; }

	virtual void CollisionPause() override;
	virtual void CollisionActive() override;

private:
	//�I�u�W�F�N�g�ɐݒ肷��p�̃{�b�N�X�i���S���I�u�W�F�N�g�̒��S�ɂ���j
	AABB objectBox;
	//�����蔻�肷��Ƃ��Ɏg���{�b�N�X�i���S�����[���h���W�̒��S�ɂ���j
	AABB worldBox;
};

