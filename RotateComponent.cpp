#include "RotateComponent.h"
#include "GameObject.h"
#include "InputSystem.h"

RotateComponent::RotateComponent(GameObject* argOwner, int argUpdateOrder)
	:Component(argOwner)
{
}

void RotateComponent::Update(float argDeltaTime)
{
	Vector3 pos = owner->GetPosition();
	float rad;
	if (right)
	{
		rad = Math::ToRadians(90.0f);
	}
	else
	{
		rad = Math::ToRadians(-90.0f);
	}
	if (pos.y > 850)
	{
		Quaternion rot = owner->GetRotation();
		Quaternion inc(Vector3::UnitX, rad);
		rot = Quaternion::Concatenate(rot,inc);
		owner->SetRotation(rot);
		owner->SetPosition(Vector3(pos.x,850.0f,pos.z));
	}
	else if (pos.y < -850)
	{
		Quaternion rot = owner->GetRotation();
		Quaternion inc(Vector3::UnitX, rad);
		rot = Quaternion::Concatenate(rot, inc);
		owner->SetRotation(rot);
		owner->SetPosition(Vector3(pos.x, -850.0f, pos.z));

	}
	else if (pos.z > 1850)
	{
		Quaternion rot = owner->GetRotation();
		Quaternion inc(Vector3::UnitX, rad);
		rot = Quaternion::Concatenate(rot, inc);
		owner->SetRotation(rot);
		owner->SetPosition(Vector3(pos.x, pos.y, 1850));

	}
	else if (pos.z < 150)
	{
		Quaternion rot = owner->GetRotation();
		Quaternion inc(Vector3::UnitX, rad);
		rot = Quaternion::Concatenate(rot, inc);
		owner->SetRotation(rot);
		owner->SetPosition(Vector3(pos.x, pos.y, 150));
	}
}

void RotateComponent::ProcessInput(const InputState & state)
{
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_D))
	{
		right = true;
	}
	else if (state.Keyboard.GetKeyState(SDL_SCANCODE_A))
	{
		right = false;
	}
}
