#pragma once

#include <vector>
#include <functional>
#include "Math.h"
#include "Collision.h"

class Game;
class GameObject;
class BoxCollider;
class SphereCollider;

class PhysicsWorld
{
public:
    PhysicsWorld(Game* argGame);

    void HitCheck();

    void AddBox(BoxCollider* argBox);
    void RemoveBox(BoxCollider* argBox);
	void AddSphere(SphereCollider* argSphere);
	void RemoveSphere(SphereCollider* argSphere);

private:

	void SphereAndSphere();
	void BoxAndBox();
	void SphereAndBox();

    Game * game;
    std::vector<BoxCollider*> boxes;
	std::vector<SphereCollider*> spheres;

};

