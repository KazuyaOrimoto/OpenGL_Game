#pragma once
#include "ObstacleBox.h"


class MeshComponent;
class BoxCollider;
class PlayerObject;

class SlidingObject : public ObstacleBox
{
public:
	SlidingObject();
	~SlidingObject();

	/**
	@brief	フレーム毎の処理
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void UpdateGameObject(float _deltaTime) override;

	virtual void OnCollision(const GameObject& _hitObject) override;

	void HitObstacle(const ObstacleBox & _hitObstacle);

private:
	MeshComponent* meshComp;
	BoxCollider* boxCollider;
	GameObject* player;
};

