#include "RotateComponent.h"
#include "GameObject.h"
#include "InputSystem.h"

RotateComponent::RotateComponent(GameObject* argOwner, int argUpdateOrder)
	:Component(argOwner)
{
}

/**
@brief	フレーム毎の処理
@param	最後のフレームを完了するのに要した時間
*/
void RotateComponent::Update(float argDeltaTime)
{
	Vector3 pos = owner->GetPosition();
	//このフレームで入力されたのが右なら右回転、左なら左回転用の角度を代入する
	float rad = right ? Math::ToRadians(90.0f) : Math::ToRadians(-90.0f);
	//右の壁についたとき
	if (pos.y > 850)
	{
		Quaternion rot = owner->GetRotation();
		Quaternion inc(Vector3::UnitX, rad);
		rot = Quaternion::Concatenate(rot,inc);
		owner->SetRotation(rot);
		owner->SetPosition(Vector3(pos.x,850.0f,pos.z));
	}
	//左の壁についたとき
	else if (pos.y < -850)
	{
		Quaternion rot = owner->GetRotation();
		Quaternion inc(Vector3::UnitX, rad);
		rot = Quaternion::Concatenate(rot, inc);
		owner->SetRotation(rot);
		owner->SetPosition(Vector3(pos.x, -850.0f, pos.z));

	}
	//上の壁についたとき
	else if (pos.z > 1850)
	{
		Quaternion rot = owner->GetRotation();
		Quaternion inc(Vector3::UnitX, rad);
		rot = Quaternion::Concatenate(rot, inc);
		owner->SetRotation(rot);
		owner->SetPosition(Vector3(pos.x, pos.y, 1850));

	}
	//下の壁についたとき
	else if (pos.z < 150)
	{
		Quaternion rot = owner->GetRotation();
		Quaternion inc(Vector3::UnitX, rad);
		rot = Quaternion::Concatenate(rot, inc);
		owner->SetRotation(rot);
		owner->SetPosition(Vector3(pos.x, pos.y, 150));
	}
}

/**
@brief	入力処理
@param	InputState構造体
*/
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
