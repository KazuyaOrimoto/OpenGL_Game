#pragma once
#include "GameObject.h"

class BikeObject;

class ObstacleCheck : public GameObject
{
public:
	ObstacleCheck(BikeObject* _bike);
	~ObstacleCheck();

	/**
	@brief	フレーム毎の処理
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void UpdateGameObject(float _deltaTime) override;

	virtual void OnCollision(const GameObject& _hitObject) override;

	bool OnObstacle() { return onObstacle; }

private:
	BikeObject* bike;

	bool onObstacle;
	//障害物と衝突していたかどうか
	bool wasCollidedObstacle;
};

