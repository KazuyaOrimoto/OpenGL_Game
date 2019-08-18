#pragma once
#include "GameObject.h"
class WallObject :
	public GameObject
{
public:
	WallObject(Game* game,int i);
	~WallObject();

	/**
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float argDaltaTime) override;

private:
	GameObject* player;
};

