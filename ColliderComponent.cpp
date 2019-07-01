#include "ColliderComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "PhysicsWorld.h"

ColliderComponent::ColliderComponent(GameObject* argOwner, int argUpdateOrder, int argCollisionOrder)
	: Component(argOwner,argUpdateOrder)
	, isTrigger(false)
	, collisionOrder(argCollisionOrder)
{
}


ColliderComponent::~ColliderComponent()
{
}