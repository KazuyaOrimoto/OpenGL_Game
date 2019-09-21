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

ObstacleMapLoder* ObstacleObject::mapLoder = nullptr;

ObstacleObject::ObstacleObject(Game* _game, int _i)
    :GameObject(_game)
    , player(nullptr)
{
	if (mapLoder == nullptr)
	{
		mapLoder = new ObstacleMapLoder();
	}
    player = GAME_OBJECT_MANAGER->FindGameObject(Tag::Player);
    CreateObstacle(5000.0f + _i * 2000.0f);

}

ObstacleObject::~ObstacleObject()
{
}

void ObstacleObject::UpdateGameObject(float _deltaTime)
{
    if (player->GetPosition().x - 500.0f > position.x)
    {
        CreateObstacle(position.x + 20 * 2000.0f);
    }
}

void ObstacleObject::CreateObstacle(float _depth)
{
	rapidjson::Document* doc = mapLoder->GetRandamMap();
	rapidjson::Value& mapJson = (*doc)["Obstacles"];
    for (Uint16 i = 0; i < mapJson.Size(); i++)
    {

        ObstacleBox* box = dynamic_cast<ObstacleBox*>(OBSTACLE_MANAGER->GetObstacle());
        if (box == nullptr)
        {
            return;
        }
        box->SetPosition(Vector3(_depth, mapJson[i]["x"].GetFloat(), mapJson[i]["y"].GetFloat()));
        box->UseObstacle();
        SetPosition(Vector3(_depth, -0.0f, 0.0f));


		//size = mapJson[i].GetUint();
  //      if (size != 0)
  //      {
  //          ten = i / 10;
  //          one = i % 10;
  //          ObstacleBox* box = dynamic_cast<ObstacleBox*>(OBSTACLE_MANAGER->GetObstacle());
		//	if (box == nullptr)
		//	{
		//		return;
		//	}
  //          box->SetPosition(Vector3(_depth, one * 200.0f, ten * 200.0f));
  //          box->UseObstacle();
		//	box->SetScale(2 * 100.0f);
  //          
  //      }
    }
}
