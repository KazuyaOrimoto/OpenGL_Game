#pragma once
#include "GameObject.h"

class BikeObject;

class JumpCheck :
	public GameObject
{
public:
	JumpCheck(BikeObject* _bike);
	~JumpCheck();

	/**
	@brief	�t���[�����̏���
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void UpdateGameObject(float _deltaTime) override;


private:
	BikeObject* bike;

	bool canJump;
};

