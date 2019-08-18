#pragma once
#include "Component.h"
#include "Math.h"

class DrilObject;

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

	int GetTorque() { return torque; }

    bool CanMove() { return canMove; }
	void AddTorque();
	void SubTorque();
private:

	bool right;
	//��]�œ�����
	int  torque;
    Quaternion target;
    float f;
    bool canMove;
    Quaternion rot;
};

