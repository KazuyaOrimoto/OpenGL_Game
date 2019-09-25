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
    CreateObstacle(5000.0f + _i * 6000.0f);

}

ObstacleObject::~ObstacleObject()
{
}

void ObstacleObject::UpdateGameObject(float _deltaTime)
{
    if (player->GetPosition().x - 500.0f > position.x)
    {
        CreateObstacle(position.x + 20 * 6000.0f);
    }
}

void ObstacleObject::CreateObstacle(float _depth)
{
	rapidjson::Document* doc = mapLoder->GetRandamMap();
	rapidjson::Value& Obstacles = (*doc)["Obstacles"];
    for (Uint16 i = 0; i < Obstacles.Size(); i++)
    {
        ObstacleBox* box = dynamic_cast<ObstacleBox*>(OBSTACLE_MANAGER->GetObstacle(Obstacles[i]["type"].GetString()));
        if (box == nullptr)
        {
            return;
        }
        box->SetPosition(Vector3(_depth, Obstacles[i]["x"].GetFloat(), Obstacles[i]["y"].GetFloat()));
        box->UseObstacle();
        SetPosition(Vector3(_depth, -0.0f, 0.0f));
    }
}
