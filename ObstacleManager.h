#pragma once

#include <vector>

#define OBSTACLE_MANAGER ObstacleManager::GetInstance()

class PlayerObject;
class ObstacleObject;

class ObstacleManager
{
public:
	static ObstacleManager* GetInstance() { return obstacle; }
	static void CreateInstance();
	static void DeleteInstance();

	void AddPlayer(PlayerObject* argPlayer) { player = argPlayer; }
	void RemovePlayer() { player = nullptr; }
	void AddOnstacle(ObstacleObject* argObstacle);
	void RemoveObstacle(ObstacleObject* argObstacle);

    void HitObstacle(ObstacleObject* argObstacle);

private:
	ObstacleManager();

	static ObstacleManager* obstacle;

	PlayerObject* player;
	std::vector<ObstacleObject*> obstacles;

};

