#include "PhysicsWorld.h"
#include <algorithm>
#include <SDL.h>
#include "BoxComponent.h"
#include "SphereCollider.h"
#include "GameObject.h"

PhysicsWorld::PhysicsWorld(Game * argGame)
	:game(argGame)
{
}

bool PhysicsWorld::SegmentCast(LineSegment & argLine, CollisionInfo & outCollision)
{
	bool collided = false;

	float closestT = Math::Infinity;
	Vector3 norm;

	for (auto box : boxes)
	{
		float t;
		if (Intersect(argLine, box->GetWorldBox(), t, norm))
		{
			if (t < closestT)
			{
				outCollision.point = argLine.PointOnSegment(t);
				outCollision.normal = norm;
				outCollision.box = box;
				outCollision.gameObject = box->GetOwner();
				collided = true;
			}
		}
	}
	return collided;
}

void PhysicsWorld::TestPairwise(std::function<void(GameObject*, GameObject*)> argFunc)
{
	for (size_t i = 0; i < boxes.size(); i++)
	{
		for (size_t j = i + 1; j < boxes.size(); j++)
		{
			BoxComponent* a = boxes[i];
			BoxComponent* b = boxes[j];
			if (Intersect(a->GetWorldBox(), b->GetWorldBox()))
			{
				argFunc(a->GetOwner(), b->GetOwner());
			}
		}

	}
}

void PhysicsWorld::TestSweepAndPrune(std::function<void(GameObject*, GameObject*)> argFunc)
{
	std::sort(boxes.begin(), boxes.end(), [](BoxComponent* a, BoxComponent*b)
		{
			return a->GetWorldBox().min.x < b->GetWorldBox().min.x;
		});

	for (size_t i = 0; i < boxes.size(); i++)
	{
		BoxComponent* a = boxes[i];
		float max = a->GetWorldBox().max.x;
		for (size_t j = i + 1; j < boxes.size(); j++)
		{
			BoxComponent*b = boxes[j];

			if (b->GetWorldBox().min.x > max)
			{
				break;
			}
			else if (Intersect(a->GetWorldBox(), b->GetWorldBox()))
			{
				argFunc(a->GetOwner(), b->GetOwner());
			}
		}
	}
}

void PhysicsWorld::HitCheck()
{
	for (size_t i = 0; i < spheres.size(); i++)
	{
		for (size_t j =i + 1; j < spheres.size(); j++)
		{
			bool hit = Intersect(spheres[i]->GetWorldSphere(), spheres[j]->GetWorldSphere());

			if (hit)
			{
				SphereCollider* sphereA = spheres[i];
				SphereCollider* sphereB = spheres[j];

				sphereA->OnCollision(*(sphereB->GetOwner()));
				sphereB->OnCollision(*(sphereA->GetOwner()));
			}
		}
	}
}

void PhysicsWorld::AddBox(BoxComponent * argBox)
{
	boxes.emplace_back(argBox);
}

void PhysicsWorld::RemoveBox(BoxComponent * argBox)
{
	auto iter = std::find(boxes.begin(), boxes.end(), argBox);
	if (iter != boxes.end())
	{
		std::iter_swap(iter, boxes.end() - 1);
		boxes.pop_back();
	}
}

void PhysicsWorld::AddSphere(SphereCollider * argSphere)
{
	spheres.emplace_back(argSphere);
}

void PhysicsWorld::RemoveSphere(SphereCollider * argSphere)
{
	auto iter = std::find(spheres.begin(), spheres.end(), argSphere);
	if (iter != spheres.end())
	{
		std::iter_swap(iter, spheres.end() - 1);
		spheres.pop_back();
	}

}
