#include "AutoRunComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"
#include "DrilObject.h"

AutoRunComponent::AutoRunComponent(GameObject* owner, int updateOrder)
	: Component(owner, updateOrder)
	, forwardSpeed(0.0f)
{
}

void AutoRunComponent::Update(float deltaTime)
{
	if (deltaTime > 0.03)
	{
		return;
	}
	Vector3 pos = owner->GetPosition();
	pos += owner->GetForward() * forwardSpeed * deltaTime;
	owner->SetPosition(pos);
    dril->SetPosition(pos);
}
