#include "ObstacleObject.h"
#include "Game.h"
#include "Collision.h"
#include "ObstacleManager.h"
#include "ObstacleBox.h"
#include "GameObjectManager.h"
#include <fstream>
#include <sstream>
#include <document.h>
#include <string>
#include "ObstacleMapLoder.h"
#include "BoostItem.h"

ObstacleMapLoder* ObstacleObject::mapLoder = nullptr;

ObstacleObject::ObstacleObject(int _i)
    :GameObject()
    , player(nullptr)
{
	if (mapLoder == nullptr)
	{
		mapLoder = new ObstacleMapLoder();
	}
    player = GameObject::FindGameObject(Tag::Player);
    CreateObstacle(5000.0f + _i * StaticObstacle::ObstacleDistanceNum);
	i = _i;
	name = "Obstacle";
}

ObstacleObject::~ObstacleObject()
{
}

void ObstacleObject::UpdateGameObject(float _deltaTime)
{
	if (player == nullptr)
	{
		return;
	}
    if (player->GetPosition().x - 500.0f > position.x)
    {
        CreateObstacle(position.x + StaticObstacle::ObstacleMaxNum * StaticObstacle::ObstacleDistanceNum);
    }
}

void ObstacleObject::CreateObstacle(float _depth)
{
	rapidjson::Document* doc = mapLoder->GetRandamMap();
	rapidjson::Value& Obstacles = (*doc)["Obstacles"];
    for (Uint16 i = 0; i < Obstacles.Size(); i++)
    {
		std::string type = Obstacles[i]["type"].GetString();
		if (type == "Obstacle")
		{
			ObstacleBox* box = static_cast<ObstacleBox*>(OBSTACLE_MANAGER->GetObstacle(type));
			if (box == nullptr)
			{
				return;
			}
			box->SetPosition(Vector3(_depth, Obstacles[i]["x"].GetFloat(), Obstacles[i]["y"].GetFloat()));
			box->UseObstacle();
		}

		else if (type == "Boost")
		{
			GameObject* gameObject = new BoostItem();
			gameObject->SetPosition(Vector3(_depth,Obstacles[i]["x"].GetFloat(),Obstacles[i]["y"].GetFloat()));
		}
    }
    SetPosition(Vector3(_depth, 0.0f, 0.0f));
}
