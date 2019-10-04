#pragma once
#include "GameObject.h"

class BikeObject;

class JumpCheck :
	public GameObject
{
public:
	JumpCheck(BikeObject* _bike);
	~JumpCheck();

	/**
	@brief	フレーム毎の処理
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void UpdateGameObject(float _deltaTime) override;


private:
	BikeObject* bike;

	bool canJump;
};

