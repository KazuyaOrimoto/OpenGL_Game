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
	//このフレームで入力されたのが右なら右回転、左なら左回転用の角度を代入する
	float rad = right ? Math::ToRadians(90.0f) : Math::ToRadians(-90.0f);
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
