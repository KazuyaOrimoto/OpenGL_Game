#pragma once
#include "Component.h"
#include "Collision.h"

class GameObject;

class ColliderComponent : public Component
{
public:
    /**
    @param	アタッチするゲームオブジェクトのポインタ
    @param	コンポーネントの更新順番（数値が小さいほど早く更新される）
    @param  当たり判定時に、めり込みから動かく処理の優先度を決める数値
    */
	ColliderComponent(GameObject* _owner, int _updateOrder = 200,int _collisionOrder = 100);
	virtual ~ColliderComponent();

	int GetCollisionOrder() const { return collisionOrder; }

	//オブジェクトが球に当たった時にめりこみからずらす処理
	virtual void ShiftObject(const Sphere& _hirSphere) {}
	//オブジェクトが平面に当たった時にめりこみからずらす処理
	virtual void ShiftObject(const Plane& _hitPlane) {}
	//オブジェクトがAABBに当たった時にめりこみからずらす処理
	virtual void ShiftObject(const AABB& _hitBox) {}
	//オブジェクトがカプセルに当たった時にめりこみからずらす処理
	virtual void ShiftObject(const Capsule& _hitCapsule) {}

	virtual void CollisionPause() = 0;
	virtual void CollisionActive() = 0;


private:
    //実体を伴う当たり判定をするかどうか
	bool isTrigger;
	//数値が大きい方を優先してめり込みから動かす処理をする（0以下は動かさない）
	int collisionOrder;
    //

};

