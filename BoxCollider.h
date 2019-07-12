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
	//オブジェクトに設定する用のボックス（中心をオブジェクトの中心にする）
	AABB objectBox;
	//当たり判定するときに使うボックス（中心をワールド座標の中心にする）
	AABB worldBox;
};

