//=============================================================================
//	@file	GameOverLogo.h
//	@brief	�Q�[���I�[�o�[�̃V�[���̃��S�̃I�u�W�F�N�g
//	@autor	���{ �a��
//	@date	2020/02/29
//=============================================================================

#pragma once
#include "GameObject.h"
class GameOverLogo :
	public GameObject
{
public:
	GameOverLogo();
	~GameOverLogo();

	virtual void GameObjectInput(const InputState & _state) override;
};

