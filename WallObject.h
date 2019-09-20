#pragma once
#include "GameObject.h"
class WallObject :
	public GameObject
{
public:
	WallObject(Game* _game,int _i);
	~WallObject();

	/**
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime) override;

private:
	GameObject* player;
};

