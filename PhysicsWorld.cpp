#include "PhysicsWorld.h"
#include <algorithm>
#include <SDL.h>
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "GameObject.h"
#include "ColliderComponent.h"

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

void PhysicsWorld::HitCheck(BoxCollider* _box)
{
	//コライダーの親オブジェクトがActiveじゃなければ終了する
	if (_box->GetOwner()->GetState() != State::Active)
	{
		return;
	}
	for (auto itr : spheres)
	{
		//コライダーの親オブジェクトがActiveじゃなければ終了する
		if (itr->GetOwner()->GetState() != State::Active)
		{
			continue;
		}
		bool hit = Intersect(itr->GetWorldSphere(),_box->GetWorldBox());
		if (hit)
		{
			onCollisionFunc func = collisionFunction.at(_box);
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_box->GetOwner()));
		}
	}
	for (auto itr : boxes)
	{
		if (itr == _box)
		{
			continue;
		}
		//コライダーの親オブジェクトがActiveじゃなければ終了する
		if (itr->GetOwner()->GetState() != State::Active)
		{
			continue;
		}
		bool hit = Intersect(itr->GetWorldBox(), _box->GetWorldBox());
		if (hit)
		{
			onCollisionFunc func = collisionFunction.at(_box);
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_box->GetOwner()));
		}
	}
}

void PhysicsWorld::HitCheck(SphereCollider * _sphere)
{
	//コライダーの親オブジェクトがActiveじゃなければ終了する
	if (_sphere->GetOwner()->GetState() != State::Active)
	{
		return;
	}
	for (auto itr : spheres)
	{
		if (itr == _sphere)
		{
			continue;
		}
		//コライダーの親オブジェクトがActiveじゃなければ終了する
		if (itr->GetOwner()->GetState() != State::Active)
		{
			continue;
		}
		bool hit = Intersect(itr->GetWorldSphere(), _sphere->GetWorldSphere());
		if (hit)
		{
			onCollisionFunc func = collisionFunction.at(_sphere);
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_sphere->GetOwner()));
		}
	}
	for (auto itr : boxes)
	{
		//コライダーの親オブジェクトがActiveじゃなければ終了する
		if (itr->GetOwner()->GetState() != State::Active)
		{
			continue;
		}
		bool hit = Intersect(_sphere->GetWorldSphere(),itr->GetWorldBox());
		if (hit)
		{
			onCollisionFunc func = collisionFunction.at(_sphere);
			func(*(itr->GetOwner()));
			func = collisionFunction.at(itr);
			func(*(_sphere->GetOwner()));
		}
	}
}

void PhysicsWorld::AddBox(BoxCollider * _box, onCollisionFunc _func)
{
	boxes.emplace_back(_box);
    //コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
    collisionFunction.insert(std::make_pair(dynamic_cast<ColliderComponent*>(_box), _func));
}

void PhysicsWorld::RemoveBox(BoxCollider * _box)
{
	auto iter = std::find(boxes.begin(), boxes.end(), _box);
	if (iter != boxes.end())
	{
		std::iter_swap(iter, boxes.end() - 1);
		boxes.pop_back();
	}
    collisionFunction.erase(_box);
}

void PhysicsWorld::AddSphere(SphereCollider * _sphere, onCollisionFunc _func)
{
	spheres.emplace_back(_sphere);
    //コライダーのポインタと親オブジェクトの当たり判定時関数ポインタ
    collisionFunction.insert(std::make_pair(dynamic_cast<ColliderComponent*>(_sphere), _func));
}

void PhysicsWorld::RemoveSphere(SphereCollider * _sphere)
{
	auto iter = std::find(spheres.begin(), spheres.end(), _sphere);
	if (iter != spheres.end())
	{
		std::iter_swap(iter, spheres.end() - 1);
		spheres.pop_back();
	}
    collisionFunction.erase(_sphere);
}

void PhysicsWorld::SphereAndSphere()
{
	for (size_t i = 0; i < spheres.size(); i++)
	{
		if (spheres[i]->GetOwner()->GetState() != Active)
		{
			continue;
		}
		for (size_t j = i + 1; j < spheres.size(); j++)
		{
			if (spheres[j]->GetOwner()->GetState() != Active)
			{
				continue;
			}
			bool hit = Intersect(spheres[i]->GetWorldSphere(), spheres[j]->GetWorldSphere());

			if (hit)
			{
				SphereCollider* sphereA = spheres[i];
				SphereCollider* sphereB = spheres[j];

				//sphereA->GetOwner()->OnCollision(*(sphereB->GetOwner()));
				//sphereB->GetOwner()->OnCollision(*(sphereA->GetOwner()));
			}
		}
	}
}

void PhysicsWorld::BoxAndBox()
{
	for (size_t i = 0; i < boxes.size(); i++)
	{
		if (boxes[i]->GetOwner()->GetState() != Active)
		{
			continue;
		}
		for (size_t j = i + 1; j < boxes.size(); j++)
		{
			if (boxes[j]->GetOwner()->GetState() != Active)
			{
				continue;
			}
			bool hit = Intersect(boxes[i]->GetWorldBox(), boxes[j]->GetWorldBox());

			if (hit)
			{
				BoxCollider* boxA = boxes[i];
				BoxCollider* boxB = boxes[j];

				//boxA->GetOwner()->OnCollision(*(boxB->GetOwner()));
				//boxB->GetOwner()->OnCollision(*(boxA->GetOwner()));
			}
		}
	}
}

void PhysicsWorld::SphereAndBox()
{
	for (size_t i = 0; i < spheres.size(); i++)
	{
		if (spheres[i]->GetOwner()->GetState() != Active)
		{
			continue;
		}
		for (size_t j = 0; j < boxes.size(); j++)
		{
			if (boxes[j]->GetOwner()->GetState() != Active)
			{
				continue;
			}
			bool hit = Intersect(spheres[i]->GetWorldSphere(), boxes[j]->GetWorldBox());

			if (hit)
			{
				//spheres[i]->GetOwner()->OnCollision(*(boxes[j]->GetOwner()));
				//boxes[j]->GetOwner()->OnCollision(*(spheres[i]->GetOwner()));
			}
		}
	}
}
