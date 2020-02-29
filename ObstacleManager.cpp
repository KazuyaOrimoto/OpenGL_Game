//=============================================================================
//	@file	ObstacleManager.h
//	@brief	障害物を管理
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#include "ObstacleManager.h"
#include "PlayerObject.h"
#include "ObstacleBox.h"
#include "GameObject.h"
#include "BoostItem.h"

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

void ObstacleManager::AddBoostItem(BoostItem * _boost)
{
	boostItems.emplace_back(_boost);
}

void ObstacleManager::RemoveBoostItem(BoostItem * _boost)
{
	auto iter = std::find(boostItems.begin(), boostItems.end(), _boost);
	if (iter != boostItems.end())
	{
		std::iter_swap(iter, boostItems.end() - 1);
		boostItems.pop_back();
	}
}

ObstacleBox* ObstacleManager::GetObstacle(std::string _type)
{
	for (auto itr : obstacles)
	{
		if (itr->GetState() == Paused)
		{
			if (_type == "Obstacle")
			{
				if (itr->GetTag() == Tag::Obstacle)
				{
					return itr;
				}
			}
		}
	}
	return nullptr;
}

BoostItem * ObstacleManager::GetBoostItem(std::string _type)
{
	for (auto itr : boostItems)
	{
		if (itr->GetState() == Paused)
		{
			if (_type == "Boost")
			{
				if (itr->GetTag() == Tag::Boost)
				{
					return itr;
				}
			}
		}
	}
	return nullptr;
}

ObstacleManager::ObstacleManager()
{

}
