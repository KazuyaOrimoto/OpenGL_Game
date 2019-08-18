#pragma once

#include <vector>

#define OBSTACLE_MANAGER ObstacleManager::GetInstance()

class PlayerObject;
class ObstacleBox;

class ObstacleManager
{
public:
	static ObstacleManager* GetInstance() { return obstacle; }
	static void CreateInstance();
	static void DeleteInstance();

	void AddPlayer(PlayerObject* argPlayer) { player = argPlayer; }
	void RemovePlayer() { player = nullptr; }
	void AddOnstacle(ObstacleBox* argObstacle);
	void RemoveObstacle(ObstacleBox* argObstacle);

	ObstacleBox* GetObstacle();

private:
	ObstacleManager();

	static ObstacleManager* obstacle;

	PlayerObject* player;
	std::vector<ObstacleBox*> obstacles;

};

