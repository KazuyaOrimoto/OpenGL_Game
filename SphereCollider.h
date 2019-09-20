#pragma once
#include "ColliderComponent.h"


class SphereCollider :
	public ColliderComponent
{
public:
	SphereCollider(GameObject* _owner, int _updateOrder = 100, int _collisionOrder = 100);
	~SphereCollider();
	
	void OnUpdateWorldTransform() override;

	void SetObjectSphere(const Sphere& _sphere) { objectSphere = _sphere; }
	Sphere GetWorldSphere() const { return worldSphere; }

private:
	//オブジェクトに設定する用の球（中心をオブジェクトの中心にする）
	Sphere objectSphere;
	//当たり判定するときに使う球（中心をワールド座標の中心にする）
	Sphere worldSphere;

};

