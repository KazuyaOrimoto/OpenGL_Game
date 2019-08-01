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


	//オブジェクトが球に当たった時にめりこみからずらす処理
	virtual void ShiftObject(const Sphere& argHirSphere) {}
	//オブジェクトが平面に当たった時にめりこみからずらす処理
	virtual void ShiftObject(const Plane& argHitPlane) {}
	//オブジェクトがAABBに当たった時にめりこみからずらす処理
	virtual void ShiftObject(const AABB& argHitBox) {}
	//オブジェクトがカプセルに当たった時にめりこみからずらす処理
	virtual void ShiftObject(const Capsule& argHitCapsule) {}

private:
	bool isTrigger;
	//数値が大きい方を優先してめり込みから動かす処理をする（0以下は動かさない）
	int collisionOrder;
};

