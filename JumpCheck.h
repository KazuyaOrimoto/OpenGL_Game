#pragma once
#include "GameObject.h"

class BikeObject;

class JumpCheck : public GameObject
{
public:
	JumpCheck(BikeObject* _bike);
	~JumpCheck();

	/**
	@brief	フレーム毎の処理
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void UpdateGameObject(float _deltaTime) override;

	virtual void OnCollision(const GameObject& _hitObject) override;

	bool CanJump() { return canJump; }

private:
	BikeObject* bike;

	bool canJump;
	//障害物と衝突していたかどうか
	bool wasCollidedObstacle;
};

