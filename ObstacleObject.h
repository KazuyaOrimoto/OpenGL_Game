//=============================================================================
//	@file	ObstacleObject.h
//	@brief	同じ区間にある障害物の一括作成
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#pragma once
#include "GameObject.h"
#include <fstream>
#include <sstream>
#include <document.h>
#include <vector>

class MeshComponent;
class BoxCollider;
class PlayerObject;
class ObstacleMapLoder;

namespace StaticObstacle
{
	static const int ObstacleMaxNum = 5;
	static const float ObstacleDistanceNum = 4000.0f;
}

class ObstacleObject : public GameObject
{
public:
	ObstacleObject(int _i);
	~ObstacleObject();

	/**
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime) override;

	virtual void SetPosition(const Vector3& _pos) override { position = _pos; recomputeWorldTransform = true; }

private:

	static ObstacleMapLoder* mapLoder;
    void CreateObstacle(float _depth);
	GameObject* player;
	int i;

};