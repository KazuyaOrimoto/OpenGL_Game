#pragma once
#include "GameObject.h"
class Titlelogo :
	public GameObject
{
public:
	Titlelogo();
	~Titlelogo();

	/**
	@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void UpdateGameObject(float _deltaTime) override;

	virtual void GameObjectInput(const InputState& _state) override;

};

