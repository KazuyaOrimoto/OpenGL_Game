#pragma once

#include <vector>
#include <map>
#include <functional>
#include "Math.h"
#include "Collision.h"

#define PHYSICS PhysicsWorld::GetInstance()

class Game;
class GameObject;
class BoxCollider;
class SphereCollider;
class ColliderComponent;

class PhysicsWorld
{
public:
	static PhysicsWorld* GetInstance() { return physics; }
	static void CreateInstance();
	static void DeleteInstance();

	//当たり判定
    void HitCheck();
    void HitCheck(BoxCollider* _box);
    void HitCheck(SphereCollider* _sphere);

    void AddBox(BoxCollider* _box);
    void RemoveBox(BoxCollider* _box);
	void AddSphere(SphereCollider* _sphere);
	void RemoveSphere(SphereCollider* _sphere);

private:
	//コンストラクタの隠蔽
	PhysicsWorld();

	static PhysicsWorld* physics;

	void SphereAndSphere();
	void BoxAndBox();
	void SphereAndBox();

    std::vector<BoxCollider*> boxes;
	std::vector<SphereCollider*> spheres;
    std::map<ColliderComponent*, std::function<void(GameObject&)>> collisionFunction;

};

