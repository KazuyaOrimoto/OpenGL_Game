//=============================================================================
//	@file	Titlelogo.h
//	@brief	�^�C�g���̃V�[���̃��S�̃I�u�W�F�N�g
//	@autor	���{ �a��
//	@date	2020/02/29
//=============================================================================

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


private:
	bool change;
};

