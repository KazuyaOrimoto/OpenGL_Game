#include "AutoRunComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"
#include "BikeObject.h"

AutoRunComponent::AutoRunComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
	, forwardSpeed(0.0f)
{
}

void AutoRunComponent::Update(float _deltaTime)
{
	if (_deltaTime > 0.02)
	{
		return;
	}
	Vector3 pos = owner->GetPosition();
	pos += owner->GetForward() * 500 * _deltaTime;
	owner->SetPosition(pos);
    dril->SetPosition(pos);
}
