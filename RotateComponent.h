#pragma once
#include "Component.h"
class RotateComponent : public Component
{
public:
	RotateComponent(GameObject* argOwner, int argUpdateOrder = 10);

	/**
	@brief	�t���[�����̏���
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void Update(float argDeltaTime);

	/**
	@brief	���͏���
	@param	InputState�\����
	*/
	virtual void ProcessInput(const struct InputState& state);

private:

	bool right;
};

