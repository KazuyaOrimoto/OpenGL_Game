#include "ObstacleManager.h"
#include "PlayerObject.h"
#include "ObstacleBox.h"

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

void ObstacleManager::AddOnstacle(ObstacleBox* argObstacle)
{
	obstacles.emplace_back(argObstacle);
}

void ObstacleManager::RemoveObstacle(ObstacleBox* argObstacle)
{
	auto iter = std::find(obstacles.begin(), obstacles.end(), argObstacle);
	if (iter != obstacles.end())
	{
		std::iter_swap(iter, obstacles.end() - 1);
		obstacles.pop_back();
	}
}

ObstacleBox * ObstacleManager::GetObstacle()
{
	for (auto itr : obstacles)
	{
		if (itr->GetState() == Paused)
		{
			return itr;
		}
	}
	return nullptr;
}

ObstacleManager::ObstacleManager()
{

}
