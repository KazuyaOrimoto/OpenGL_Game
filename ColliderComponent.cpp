#include "ColliderComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "PhysicsWorld.h"

ColliderComponent::ColliderComponent(GameObject* _owner, int _updateOrder, int _collisionOrder)
	: Component(_owner, _updateOrder)
	, isTrigger(false)
	, collisionOrder(_collisionOrder)
{
}


ColliderComponent::~ColliderComponent()
{
}