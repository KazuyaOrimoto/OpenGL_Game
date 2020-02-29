//=============================================================================
//	@file	ObstacleBox.h
//	@brief	障害物のボックスのオブジェクト
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#pragma once
#include "GameObject.h"

class HDRMeshComponent;
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
	HDRMeshComponent* meshComp;
	BoxCollider* boxCollider;
	static GameObject* player;
};

