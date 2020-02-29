//=============================================================================
//	@file	ObstacleManager.h
//	@brief	障害物を管理
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#pragma once

#include <vector>
#include <string>

#define OBSTACLE_MANAGER ObstacleManager::GetInstance()

class PlayerObject;
class ObstacleBox;
class BoostItem;

class ObstacleManager
{
public:
	static ObstacleManager* GetInstance() { return obstacle; }
	static void CreateInstance();
	static void DeleteInstance();

	void AddPlayer(PlayerObject* _player) { player = _player; }
	void RemovePlayer() { player = nullptr; }
	void AddObstacle(ObstacleBox* _obstacle);
	void RemoveObstacle(ObstacleBox* _obstacle);
	void AddBoostItem(BoostItem* _boost);
	void RemoveBoostItem(BoostItem* _boost);

	ObstacleBox* GetObstacle(std::string _type);
	BoostItem* GetBoostItem(std::string _type);

private:
	ObstacleManager();

	static ObstacleManager* obstacle;

	PlayerObject* player;
	std::vector<ObstacleBox*> obstacles;
	std::vector<BoostItem*> boostItems;

};

