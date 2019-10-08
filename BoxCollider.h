#pragma once

#include "PhysicsWorld.h"
#include "ColliderComponent.h"

class BoxCollider final : public ColliderComponent
{
public:
	BoxCollider(GameObject* _owner, onCollisionFunc _func, int _updateOrder = 200, int _collisionOrder = 100);
	~BoxCollider();

	void OnUpdateWorldTransform() override;

	void SetObjectBox(const AABB& _box) { objectBox = _box; }
	AABB GetWorldBox() const { return worldBox; }

	virtual void CollisionPause() override;
	virtual void CollisionActive() override;

private:
	//オブジェクトに設定する用のボックス（中心をオブジェクトの中心にする）
	AABB objectBox;
	//当たり判定するときに使うボックス（中心をワールド座標の中心にする）
	AABB worldBox;
};

