#include "RotateComponent.h"
#include "GameObject.h"
#include "InputSystem.h"
#include "Renderer.h"

RotateComponent::RotateComponent(GameObject* argOwner, int argUpdateOrder)
	: Component(argOwner)
	, right(true)
	, torque(10)
    , f(1)
    , canMove(true)
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
    if (canMove)
    {
        if (pos.y > 850)
        {
            rot = owner->GetRotation();
            Quaternion inc(Vector3::UnitX, rad);
            target = Quaternion::Concatenate(rot, inc);
            owner->SetPosition(Vector3(pos.x, 850.0f, pos.z));
            AddTorque();
            f = 0;
            canMove = false;

            DirectionalLight& dir = RENDERER->GetDirectionalLight();
            dir.direction = Vector3::Transform(dir.direction, inc);
        }
        //左の壁についたとき
        else if (pos.y < -850)
        {
            rot = owner->GetRotation();
            Quaternion inc(Vector3::UnitX, rad);
            target = Quaternion::Concatenate(rot, inc);
            owner->SetPosition(Vector3(pos.x, -850.0f, pos.z));
            AddTorque();
            f = 0;
            canMove = false;


            DirectionalLight& dir = RENDERER->GetDirectionalLight();
            dir.direction = Vector3::Transform(dir.direction, inc);
        }
        //上の壁についたとき
        else if (pos.z > 1850)
        {
            rot = owner->GetRotation();
            Quaternion inc(Vector3::UnitX, rad);
            target = Quaternion::Concatenate(rot, inc);
            owner->SetPosition(Vector3(pos.x, pos.y, 1850));
            AddTorque();
            f = 0;
            canMove = false;


            DirectionalLight& dir = RENDERER->GetDirectionalLight();
            dir.direction = Vector3::Transform(dir.direction, inc);
        }
        //下の壁についたとき
        else if (pos.z < 150)
        {
            rot = owner->GetRotation();
            Quaternion inc(Vector3::UnitX, rad);
            target = Quaternion::Concatenate(rot, inc);
            owner->SetPosition(Vector3(pos.x, pos.y, 150));
            AddTorque();
            f = 0;
            canMove = false;


            DirectionalLight& dir = RENDERER->GetDirectionalLight();
            dir.direction = Vector3::Transform(dir.direction, inc);
        }
    }

    if (!canMove)
    {
        if (f < 1.0)
        {
            f += 0.1f;
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
        }
        
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

/**
@brief	回転したときの回転力の加算
*/
void RotateComponent::AddTorque()
{
	if (right)
	{
		if (torque < 0)
		{
			torque = -torque;
		}
		else
		{
			torque++;
		}
	}
	else
	{
		if (torque > 0)
		{
			torque = -torque;
		}
		else
		{
			torque--;
		}
	}
}

