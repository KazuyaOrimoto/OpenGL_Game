#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* argOwner, int argUpdateOrder)
	: owner(argOwner)
	, updateOrder(argUpdateOrder)
{
	owner->AddComponent(this);
}

Component::~Component()
{
	owner->RemoveComponent(this);
}

void Component::Update(float argDeltaTime)
{
}
