#pragma once

#include <vector>
#include <string>

#define OBSTACLE_MANAGER ObstacleManager::GetInstance()

class PlayerObject;
class ObstacleBox;

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

	ObstacleBox* GetObstacle(std::string _type);

private:
	ObstacleManager();

	static ObstacleManager* obstacle;

	PlayerObject* player;
	std::vector<ObstacleBox*> obstacles;

};

