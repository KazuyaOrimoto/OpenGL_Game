//=============================================================================
//	@file	WallObject.h
//	@brief	ステージの壁のオブジェクト
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#pragma once
#include "GameObject.h"
class WallObject :
	public GameObject
{
public:
	WallObject(int _i);
	~WallObject();

	/**
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime) override;

	static void GameEnd() { gameEnd = true; }

private:
	static GameObject* player;
	static bool gameEnd;
};

