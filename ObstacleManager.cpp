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

void ObstacleManager::AddObstacle(ObstacleBox* _obstacle)
{
	obstacles.emplace_back(_obstacle);
}

void ObstacleManager::RemoveObstacle(ObstacleBox* _obstacle)
{
	auto iter = std::find(obstacles.begin(), obstacles.end(), _obstacle);
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
