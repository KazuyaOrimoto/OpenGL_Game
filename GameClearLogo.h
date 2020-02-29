//=============================================================================
//	@file	GameClearLogo.h
//	@brief	ゲームクリアのシーンのロゴのオブジェクト
//	@autor	居本 和哉
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

