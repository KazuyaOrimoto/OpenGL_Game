#include "MoveComponent.h"
#include "GameObject.h"


MoveComponent::MoveComponent(GameObject* owner, int updateOrder)
	:Component(owner,updateOrder)
{
}

void MoveComponent::Update(float deltaTime)
{
}

