#include "WallManager.h"
#include "GameObject.h"
#include "PlayerObject.h"

WallManager* WallManager::wallManager = nullptr;

void WallManager::CreateInstance()
{
	if (wallManager == nullptr)
	{
		wallManager = new WallManager();
	}
}

void WallManager::DeleteInstance()
{
	if (wallManager != nullptr)
	{
		delete wallManager;
		wallManager = nullptr;
	}
}

void WallManager::UpdateWall()
{
	if (player != nullptr)
	{
		bool moveRequired;
		Vector3 wallPosition;
		const Vector3 playerPosition = player->GetPosition();
		for (auto itr : wallObjects)
		{
			wallPosition = itr->GetPosition();
			//“®‚©‚·•K—v‚ª‚ ‚é‚È‚ç
			moveRequired = playerPosition.x - 2000.0f > wallPosition.x;
			if (moveRequired)
			{
				itr->SetPosition(Vector3(wallPosition.x + 2000.0f * 20, wallPosition.y, wallPosition.z));
			}
		}
	}
}

void WallManager::AddWallObject(GameObject * argObj)
{
	wallObjects.emplace_back(argObj);
}

void WallManager::RemoveWallObject(GameObject * argObj)
{
	auto iter = std::find(wallObjects.begin(), wallObjects.end(), argObj);
	if (iter != wallObjects.end())
	{
		std::iter_swap(iter, wallObjects.end() - 1);
		wallObjects.pop_back();
	}
}

WallManager::WallManager()
{
}


WallManager::~WallManager()
{
}
