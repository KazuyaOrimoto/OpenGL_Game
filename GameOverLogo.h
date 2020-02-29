//=============================================================================
//	@file	GameOverLogo.h
//	@brief	ゲームオーバーのシーンのロゴのオブジェクト
//	@autor	居本 和哉
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

