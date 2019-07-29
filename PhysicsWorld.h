#pragma once

#include <vector>
#include <functional>
#include "Math.h"
#include "Collision.h"

#define PHYSICS PhysicsWorld::GetInstance()

class Game;
class GameObject;
class BoxCollider;
class SphereCollider;

class PhysicsWorld
{
public:
	static PhysicsWorld* GetInstance() { return physics; }
	static void CreateInstance();
	static void DeleteInstance();

	//�����蔻��
    void HitCheck();

    void AddBox(BoxCollider* argBox);
    void RemoveBox(BoxCollider* argBox);
	void AddSphere(SphereCollider* argSphere);
	void RemoveSphere(SphereCollider* argSphere);

private:
	//�R���X�g���N�^�̉B��
	PhysicsWorld();

	static PhysicsWorld* physics;

	void SphereAndSphere();
	void BoxAndBox();
	void SphereAndBox();

    std::vector<BoxCollider*> boxes;
	std::vector<SphereCollider*> spheres;

};

