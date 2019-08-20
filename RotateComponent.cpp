#include "RotateComponent.h"
#include "GameObject.h"
#include "InputSystem.h"
#include "Renderer.h"

RotateComponent::RotateComponent(GameObject* argOwner, int argUpdateOrder)
	: Component(argOwner)
	, right(true)
	, f(1)
	, canMove(true)
	, moveTorque(10)
{
}

/**
@brief	フレーム毎の処理
@param	最後のフレームを完了するのに要した時間
*/
void RotateComponent::Update(float argDeltaTime)
{
	ownerPos = owner->GetPosition();
	cameraQuat = owner->GetRotation();
    if (canMove)
    {
		//右の壁についたとき
        if (ownerPos.y > 850)
        {
			HitRightWall();
        }
        //左の壁についたとき
        else if (ownerPos.y < -850)
        {
			HitLeftWall();
        }
        //上の壁についたとき
        else if (ownerPos.z > 1850)
        {
			HitTopWall();
        }
        //下の壁についたとき
        else if (ownerPos.z < 150)
        {
			HitUnderWall();
        }
		//どの壁にもついていないとき
		else
		{
			cameraQuat = Quaternion::Slerp(rot, target, f);
		}
    }
	//移動ができない状態
	else
	{
		MoveWall();
	}

}

/**
@brief	入力処理
@param	InputState構造体
*/
void RotateComponent::ProcessInput(const InputState & state)
{
	if (!canMove)
	{
		return;
	}
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_D))
	{
		right = true;

		float rad = Math::ToRadians(10.0f);
		Quaternion inc(Vector3::UnitX, rad);
		target = Quaternion::Concatenate(rot, inc);
	}
	else if (state.Keyboard.GetKeyState(SDL_SCANCODE_A))
	{
		right = false;

		float rad = Math::ToRadians(-10.0f);
		Quaternion inc(Vector3::UnitX, rad);
		target = Quaternion::Concatenate(rot, inc);
	}
	else
	{
		target = rot;
	}
}

//壁移動
void RotateComponent::MoveWall()
{
	if (f < 1.0)
	{
		f += 0.2f;
		Quaternion temp = Quaternion::Slerp(rot, target, f);
		owner->SetRotation(temp);

	}
	else if (f > 1.0)
	{
		f = 1.0f;
		owner->SetRotation(target);
	}
	else
	{
		canMove = true;
		rot = target;
	}
}

void RotateComponent::HitRightWall()
{
	//このフレームで入力されたのが右なら右回転、左なら左回転用の角度を代入する
	float rad = right ? Math::ToRadians(90.0f) : Math::ToRadians(-90.0f);
	rot = owner->GetRotation();
	Quaternion inc(Vector3::UnitX, rad);
	target = Quaternion::Concatenate(rot, inc);
	owner->SetPosition(Vector3(ownerPos.x, 850.0f, ownerPos.z));
	f = 0;
	canMove = false;

	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3::Transform(dir.direction, inc);
}

void RotateComponent::HitLeftWall()
{
	//このフレームで入力されたのが右なら右回転、左なら左回転用の角度を代入する
	float rad = right ? Math::ToRadians(90.0f) : Math::ToRadians(-90.0f);
	rot = owner->GetRotation();
	Quaternion inc(Vector3::UnitX, rad);
	target = Quaternion::Concatenate(rot, inc);
	owner->SetPosition(Vector3(ownerPos.x, -850.0f, ownerPos.z));
	f = 0;
	canMove = false;

	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3::Transform(dir.direction, inc);
}

void RotateComponent::HitTopWall()
{
	//このフレームで入力されたのが右なら右回転、左なら左回転用の角度を代入する
	float rad = right ? Math::ToRadians(90.0f) : Math::ToRadians(-90.0f);
	rot = owner->GetRotation();
	Quaternion inc(Vector3::UnitX, rad);
	target = Quaternion::Concatenate(rot, inc);
	owner->SetPosition(Vector3(ownerPos.x, ownerPos.y, 1850));
	f = 0;
	canMove = false;

	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3::Transform(dir.direction, inc);
}

void RotateComponent::HitUnderWall()
{
	//このフレームで入力されたのが右なら右回転、左なら左回転用の角度を代入する
	float rad = right ? Math::ToRadians(90.0f) : Math::ToRadians(-90.0f);
	rot = owner->GetRotation();
	Quaternion inc(Vector3::UnitX, rad);
	target = Quaternion::Concatenate(rot, inc);
	owner->SetPosition(Vector3(ownerPos.x, ownerPos.y, 150));
	f = 0;
	canMove = false;

	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3::Transform(dir.direction, inc);
}
