//=============================================================================
//	@file	ObstacleObject.h
//	@brief	同じ区間にある障害物の一括作成
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

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
#include "WallObject.h"

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
	if (mapLoder != nullptr)
	{
		delete mapLoder;
		mapLoder = nullptr;
	}
}

void ObstacleObject::UpdateGameObject(float _deltaTime)
{
	if (player == nullptr)
	{
		return;
	}
	if (player->GetPosition().x - 1000.0f > position.x)
	{
		CreateObstacle(position.x + StaticObstacle::ObstacleMaxNum * StaticObstacle::ObstacleDistanceNum);
	}
}

void ObstacleObject::CreateObstacle(float _depth)
{
	rapidjson::Document* doc = mapLoder->GetRandamMap();
	//マップのデータがないとき
	if (doc == nullptr)
	{
		WallObject::GameEnd();
	}
	//マップのデータがあるとき
	else
	{
		rapidjson::Value& data = (*doc)["layers"];
		for (int j = 0; j < data[0]["width"].GetInt(); j++)
		{
			for (int i = 0; i < data[0]["height"].GetInt(); i++)
			{
				int mapData = data[0]["data"][(i * 10) + j].GetInt();
				switch (mapData)
				{
				case 2:
				{
					ObstacleBox* box = static_cast<ObstacleBox*>(OBSTACLE_MANAGER->GetObstacle("Obstacle"));
					if (box == nullptr)
					{
						return;
					}
					box->SetPosition(Vector3(_depth, j * 200 + (-900), (9 - i) * 200 + 100));
					box->UseObstacle();
					break;
				}
				case 3:
				{
					BoostItem* boost = static_cast<BoostItem*>(OBSTACLE_MANAGER->GetBoostItem("Boost"));
					if (boost == nullptr)
					{
						return;
					}
					boost->UseBoostItem();
					boost->SetPosition(Vector3(_depth, j * 200 + (-900), (9 - i) * 200 + 100));
					boost->SetRot(-90);
					Quaternion rot = boost->GetRotation();
					float rad = Math::ToRadians(-90);
					Quaternion inc(Vector3::UnitX, rad);
					rot = Quaternion::Concatenate(rot, inc);
					boost->SetRotation(rot);
					break;
				}
				case 4:
				{
					BoostItem* boost = static_cast<BoostItem*>(OBSTACLE_MANAGER->GetBoostItem("Boost"));
					if (boost == nullptr)
					{
						return;
					}
					boost->UseBoostItem();
					boost->SetPosition(Vector3(_depth, j * 200 + (-900), (9 - i) * 200 + 100));
					boost->SetRot(180);
					Quaternion rot = boost->GetRotation();
					float rad = Math::ToRadians(180);
					Quaternion inc(Vector3::UnitX, rad);
					rot = Quaternion::Concatenate(rot, inc);
					boost->SetRotation(rot);
					break;
				}
				case 5:
				{
					BoostItem* boost = static_cast<BoostItem*>(OBSTACLE_MANAGER->GetBoostItem("Boost"));
					if (boost == nullptr)
					{
						return;
					}
					boost->UseBoostItem();
					boost->SetPosition(Vector3(_depth, j * 200 + (-900), (9 - i) * 200 + 100));
					boost->SetRot(90);
					Quaternion rot = boost->GetRotation();
					float rad = Math::ToRadians(90);
					Quaternion inc(Vector3::UnitX, rad);
					rot = Quaternion::Concatenate(rot, inc);
					boost->SetRotation(rot);
					break;
				}
				case 6:
				{
					BoostItem* boost = static_cast<BoostItem*>(OBSTACLE_MANAGER->GetBoostItem("Boost"));
					if (boost == nullptr)
					{
						return;
					}
					boost->UseBoostItem();
					boost->SetPosition(Vector3(_depth, j * 200 + (-900), (9 - i) * 200 + 100));
					boost->SetRot(0);
					Quaternion rot = boost->GetRotation();
					float rad = Math::ToRadians(0);
					Quaternion inc(Vector3::UnitX, rad);
					rot = Quaternion::Concatenate(rot, inc);
					boost->SetRotation(rot);
					break;
				}
				default:
					break;
				}
			}
		}



		//rapidjson::Value& Obstacles = (*doc)["Obstacles"];
		//for (Uint16 i = 0; i < Obstacles.Size(); i++)
		//{
		//	std::string type = Obstacles[i]["type"].GetString();
		//	if (type == "Obstacle")
		//	{
		//		ObstacleBox* box = static_cast<ObstacleBox*>(OBSTACLE_MANAGER->GetObstacle(type));
		//		if (box == nullptr)
		//		{
		//			return;
		//		}
		//		box->SetPosition(Vector3(_depth, Obstacles[i]["x"].GetFloat(), Obstacles[i]["y"].GetFloat()));
		//		box->UseObstacle();
		//	}

		//	else if (type == "Boost")
		//	{
		//		BoostItem* gameObject = static_cast<BoostItem*>(OBSTACLE_MANAGER->GetBoostItem(type));
		//		gameObject->UseBoostItem();
		//		gameObject->SetPosition(Vector3(_depth, Obstacles[i]["x"].GetFloat(), Obstacles[i]["y"].GetFloat()));
		//		//Quaternion r = Quaternion(Vector3::UnitX, Math::ToRadians(Obstacles[i]["w"].GetInt()));

		//		gameObject->SetRot(Obstacles[i]["w"].GetInt());

		//		Quaternion rot = gameObject->GetRotation();
		//		float rad = Math::ToRadians(Obstacles[i]["w"].GetInt());
		//		Quaternion inc(Vector3::UnitX, rad);
		//		rot = Quaternion::Concatenate(rot, inc);

		//		gameObject->SetRotation(rot);
		//	}
		//}
		SetPosition(Vector3(_depth, 0.0f, 0.0f));
	}
}
