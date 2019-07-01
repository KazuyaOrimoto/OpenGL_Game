#pragma once

#include <vector>
#include <functional>
#include "Math.h"
#include "Collision.h"

class Game;
class BoxComponent;
class GameObject;
class SphereCollider;

class PhysicsWorld
{
public:
    PhysicsWorld(Game* argGame);

    struct CollisionInfo
    {
        Vector3 point;
        Vector3 normal;
        BoxComponent* box;
        GameObject* gameObject;
    };

    bool SegmentCast(LineSegment& argLine,CollisionInfo& outCollision);

    void TestPairwise(std::function<void(GameObject*,GameObject*)> argFunc);

    void TestSweepAndPrune(std::function<void(GameObject*,GameObject*)> argFunc);

    void HitCheck();

    void AddBox(BoxComponent* argBox);
    void RemoveBox(BoxComponent* argBox);
	void AddSphere(SphereCollider* argSphere);
	void RemoveSphere(SphereCollider* argSphere);

private:
    Game * game;
    std::vector<BoxComponent*> boxes;
	std::vector<SphereCollider*> spheres;

};

