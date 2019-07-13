#include "RotateComponent.h"
#include "GameObject.h"
#include "InputSystem.h"

RotateComponent::RotateComponent(GameObject* argOwner, int argUpdateOrder)
	:Component(argOwner)
{
}

/**
@brief	�t���[�����̏���
@param	�Ō�̃t���[������������̂ɗv��������
*/
void RotateComponent::Update(float argDeltaTime)
{
	Vector3 pos = owner->GetPosition();
	//���̃t���[���œ��͂��ꂽ�̂��E�Ȃ�E��]�A���Ȃ獶��]�p�̊p�x��������
	float rad = right ? Math::ToRadians(90.0f) : Math::ToRadians(-90.0f);
	//�E�̕ǂɂ����Ƃ�
	if (pos.y > 850)
	{
		Quaternion rot = owner->GetRotation();
		Quaternion inc(Vector3::UnitX, rad);
		rot = Quaternion::Concatenate(rot,inc);
		owner->SetRotation(rot);
		owner->SetPosition(Vector3(pos.x,850.0f,pos.z));
	}
	//���̕ǂɂ����Ƃ�
	else if (pos.y < -850)
	{
		Quaternion rot = owner->GetRotation();
		Quaternion inc(Vector3::UnitX, rad);
		rot = Quaternion::Concatenate(rot, inc);
		owner->SetRotation(rot);
		owner->SetPosition(Vector3(pos.x, -850.0f, pos.z));

	}
	//��̕ǂɂ����Ƃ�
	else if (pos.z > 1850)
	{
		Quaternion rot = owner->GetRotation();
		Quaternion inc(Vector3::UnitX, rad);
		rot = Quaternion::Concatenate(rot, inc);
		owner->SetRotation(rot);
		owner->SetPosition(Vector3(pos.x, pos.y, 1850));

	}
	//���̕ǂɂ����Ƃ�
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
@brief	���͏���
@param	InputState�\����
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
