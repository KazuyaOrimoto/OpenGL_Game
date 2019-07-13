#include "PhysicsWorld.h"
#include <algorithm>
#include <SDL.h>
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "GameObject.h"

PhysicsWorld* PhysicsWorld::physics = nullptr;

PhysicsWorld::PhysicsWorld()
{
}


void PhysicsWorld::CreateInstance()
{
	if (physics == nullptr)
	{
		physics = new PhysicsWorld();
	}
}

void PhysicsWorld::DeleteInstance()
{
	if (physics != nullptr)
	{
		delete physics;
		physics = nullptr;
	}
}

void PhysicsWorld::HitCheck()
{
	SphereAndSphere();
    BoxAndBox();
    SphereAndBox();
}

void PhysicsWorld::AddBox(BoxCollider * argBox)
{
	boxes.emplace_back(argBox);
}

void PhysicsWorld::RemoveBox(BoxCollider * argBox)
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

void PhysicsWorld::SphereAndSphere()
{
	for (size_t i = 0; i < spheres.size(); i++)
	{
		for (size_t j = i + 1; j < spheres.size(); j++)
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

void PhysicsWorld::BoxAndBox()
{
	for (size_t i = 0; i < boxes.size(); i++)
	{
		for (size_t j = i + 1; j < boxes.size(); j++)
		{
			bool hit = Intersect(boxes[i]->GetWorldBox(), boxes[j]->GetWorldBox());

			if (hit)
			{
				BoxCollider* boxA = boxes[i];
				BoxCollider* boxB = boxes[j];

				boxA->OnCollision(*(boxB->GetOwner()));
				boxB->OnCollision(*(boxA->GetOwner()));
			}
		}
	}
}

void PhysicsWorld::SphereAndBox()
{
	for (size_t i = 0; i < spheres.size(); i++)
	{
		for (size_t j = 0; j < boxes.size(); j++)
		{
			bool hit = Intersect(spheres[i]->GetWorldSphere(), boxes[j]->GetWorldBox());

			if (hit)
			{
				spheres[i]->OnCollision(*(boxes[j]->GetOwner()));
				boxes[j]->OnCollision(*(spheres[i]->GetOwner()));
			}
		}
	}
}
