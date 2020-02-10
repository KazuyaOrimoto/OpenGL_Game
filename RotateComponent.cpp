#include "RotateComponent.h"
#include "GameObject.h"
#include "InputSystem.h"
#include "Renderer.h"

RotateComponent::RotateComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner,_updateOrder)
	, right(true)
	, f(1)
    , addF(0.2f)
	, canMove(true)
	, moveTorque(2)
{
}

/**
@brief	フレーム毎の処理
@param	最後のフレームを完了するのに要した時間
*/
void RotateComponent::Update(float _deltaTime)
{
	ownerPos = owner->GetPosition();
	cameraQuat = owner->GetRotation();
    if (canMove)
    {
		//右の壁についたとき
        if (ownerPos.y > 950)
        {
			HitRightWall();
        }
        //左の壁についたとき
        else if (ownerPos.y < -950)
        {
			HitLeftWall();
        }
        //上の壁についたとき
        else if (ownerPos.z > 1950)
        {
			HitTopWall();
        }
        //下の壁についたとき
        else if (ownerPos.z < 50)
        {
			HitUnderWall();
        }
		//どの壁にもついていないとき
		else
		{
			if (f < 1.0)
			{
				f += addF;
				cameraQuat = Quaternion::Slerp(moveRot, target, f);

			}
			else if (f > 1.0)
			{
				f = 1.0f;
				cameraQuat = target;
			}
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
void RotateComponent::ProcessInput(const InputState & _state)
{
	if (!canMove)
	{
		return;
	}
	if (_state.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT))
	{
		if (_state.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == ButtonState::Pressed)
		{
			f = 0.0f;
            addF = 0.02f;
		}
		float rad = Math::ToRadians(moveTorque);
		Quaternion inc(Vector3::UnitX, rad);
		target = Quaternion::Concatenate(rot, inc);
		moveRot = cameraQuat;
        right = true;
	}
	else if (_state.Keyboard.GetKeyState(SDL_SCANCODE_LEFT))
	{
		if (_state.Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == ButtonState::Pressed)
		{
			f = 0.0f;
            addF = 0.02f;
        }
		float rad = Math::ToRadians(-moveTorque);
		Quaternion inc(Vector3::UnitX, rad);
		target = Quaternion::Concatenate(rot, inc);
		moveRot = cameraQuat;
        right = false;
    }
	else if (_state.Controller.GetLAxisVec().x > 0.1)
	{
		if (_state.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == ButtonState::Pressed)
		{
			f = 0.0f;
			addF = 0.02f;
		}
		float rad = Math::ToRadians(moveTorque);
		Quaternion inc(Vector3::UnitX, rad);
		target = Quaternion::Concatenate(rot, inc);
		moveRot = cameraQuat;
		right = true;
	}
	else if (_state.Controller.GetLAxisVec().x < 0.1)
	{
		if (_state.Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == ButtonState::Pressed)
		{
			f = 0.0f;
			addF = 0.02f;
		}
		float rad = Math::ToRadians(-moveTorque);
		Quaternion inc(Vector3::UnitX, rad);
		target = Quaternion::Concatenate(rot, inc);
		moveRot = cameraQuat;
		right = false;
	}
	else
	{
		f = 0.0f;
        addF = 0.2f;
        target = rot;
		moveRot = cameraQuat;
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
	owner->SetPosition(Vector3(ownerPos.x, 950.0f, ownerPos.z));
	f = 0;
    addF = 0.2f;
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
	owner->SetPosition(Vector3(ownerPos.x, -950.0f, ownerPos.z));
	f = 0;
    addF = 0.2f;
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
	owner->SetPosition(Vector3(ownerPos.x, ownerPos.y, 1950));
	f = 0;
    addF = 0.2f;
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
	owner->SetPosition(Vector3(ownerPos.x, ownerPos.y, 50));
	f = 0;
    addF = 0.2f;
    canMove = false;

	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3::Transform(dir.direction, inc);
}
