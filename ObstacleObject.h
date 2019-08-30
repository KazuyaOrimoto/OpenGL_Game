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

class ObstacleObject : public GameObject
{
public:
	ObstacleObject(Game* game,int i);
	~ObstacleObject();

	/**
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float argDaltaTime) override;

private:

	static ObstacleMapLoder* mapLoder;
    void CreateObstacle(float depth);
	GameObject* player;

};

