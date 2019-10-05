#pragma once
#include "GameObject.h"

class BikeObject;

class ObstacleCheck : public GameObject
{
public:
	ObstacleCheck(BikeObject* _bike);
	~ObstacleCheck();

	/**
	@brief	�t���[�����̏���
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void UpdateGameObject(float _deltaTime) override;

	virtual void OnCollision(const GameObject& _hitObject) override;

	bool OnObstacle() { return onObstacle; }

private:
	BikeObject* bike;

	bool onObstacle;
	//��Q���ƏՓ˂��Ă������ǂ���
	bool wasCollidedObstacle;
};

