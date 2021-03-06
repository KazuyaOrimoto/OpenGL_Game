//=============================================================================
//	@file	Titlelogo.h
//	@brief	タイトルのシーンのロゴのオブジェクト
//	@autor	居本 和哉
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
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void UpdateGameObject(float _deltaTime) override;

	virtual void GameObjectInput(const InputState& _state) override;


private:
	bool change;
};

