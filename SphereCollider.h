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
	//オブジェクトに設定する用の球（球の中心をオブジェクトの中心にする）
	Sphere objectSphere;
	//当たり判定するときに使う球（球の中心をワールド座標の中心にする）
	Sphere worldSphere;

};

