//=============================================================================
//	@file	GameClearLogo.h
//	@brief	�Q�[���N���A�̃V�[���̃��S�̃I�u�W�F�N�g
//	@autor	���{ �a��
//	@date	2020/02/29
//=============================================================================

#pragma once
#include "GameObject.h"
class GameClearLogo :
	public GameObject
{
public:
	GameClearLogo();
	~GameClearLogo();

	virtual void GameObjectInput(const InputState & _state) override;
};

