#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;
class PlayerObject;

enum  ObstacleType
{
	OBSTACLE_BOX,
	OBSTACLE_WALL
};

class ObstacleBox :public GameObject
{
public:
	ObstacleBox();
	~ObstacleBox();

	virtual void OnCollision(const GameObject& _hitObject) override;

	virtual void ResetObstacle();
	virtual void UseObstacle();

	/**
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime) override;

private:
	MeshComponent* meshComp;
	BoxCollider* boxCollider;
	GameObject* player;
};

