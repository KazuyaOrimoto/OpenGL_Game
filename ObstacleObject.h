#pragma once
#include "GameObject.h"
#include <fstream>
#include <sstream>
#include <document.h>

class MeshComponent;
class BoxCollider;
class PlayerObject;

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

	rapidjson::Document LoadMap(const std::string & argFileName);

    void CreateObstacle(float depth);
	GameObject* player;

};

