#pragma once

#include "GameObject.h"

class Ship : public GameObject
{
public:
	/**
	@param	ゲームクラスのポインタ
	*/
	Ship(Game* _game);
	~Ship();

	/**
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime) override;

private:
};

