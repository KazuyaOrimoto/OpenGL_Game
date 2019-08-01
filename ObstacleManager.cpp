#include "ObstacleManager.h"
#include "PlayerObject.h"
#include "ObstacleObject.h"

ObstacleManager* ObstacleManager::obstacle = nullptr;

void ObstacleManager::CreateInstance()
{
	if (obstacle == nullptr)
	{
		obstacle = new ObstacleManager();
	}
}

void ObstacleManager::DeleteInstance()
{
	if (obstacle != nullptr)
	{
		delete obstacle;
		obstacle = nullptr;
	}
}

void ObstacleManager::AddOnstacle(ObstacleObject* argObstacle)
{
	obstacles.emplace_back(argObstacle);
}

void ObstacleManager::RemoveObstacle(ObstacleObject* argObstacle)
{
	auto iter = std::find(obstacles.begin(), obstacles.end(), argObstacle);
	if (iter != obstacles.end())
	{
		std::iter_swap(iter, obstacles.end() - 1);
		obstacles.pop_back();
	}
}

void ObstacleManager::HitObstacle(ObstacleObject * argObstacle)
{

}

ObstacleManager::ObstacleManager()
{
}

