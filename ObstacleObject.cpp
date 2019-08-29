#include "ObstacleObject.h"
#include "Game.h"
#include "Collision.h"
#include "ObstacleManager.h"
#include "ObstacleBox.h"
#include "GameObjectManager.h"
#include <fstream>
#include <sstream>
#include <document.h>

ObstacleObject::ObstacleObject(Game* game, int i)
    :GameObject(game)
    , player(nullptr)
{
    player = GAME_OBJECT_MANAGER->FindGameObject(Tag::Player);
    CreateObstacle(5000.0f + i * 2000.0f);
}

ObstacleObject::~ObstacleObject()
{
}

void ObstacleObject::UpdateGameObject(float argDaltaTime)
{
    if (player->GetPosition().x - 500.0f > position.x)
    {
        CreateObstacle(position.x + 20 * 2000.0f);
    }
}

rapidjson::Document ObstacleObject::LoadMap(const std::string & argFileName)
{
    std::ifstream file(argFileName);
    if (!file.is_open())
    {
        SDL_Log("File not found: Map %s", argFileName.c_str());
        return nullptr;
    }

    std::stringstream fileStream;
    fileStream << file.rdbuf();
    std::string contents = fileStream.str();
    rapidjson::StringStream jsonStr(contents.c_str());
    rapidjson::Document doc;
    doc.ParseStream(jsonStr);

    return doc;
}

void ObstacleObject::CreateObstacle(float depth)
{
	rapidjson::Document doc = LoadMap("MapData/map.json");
	rapidjson::Value& mapJson = doc["map"];
    int ten;
    int one;
	int size;
    for (Uint16 i = 0; i < mapJson.Size(); i++)
    {
		size = mapJson[i].GetUint();
        if (size != 0)
        {
            ten = i / 10;
            one = i % 10;
            ObstacleBox* box = dynamic_cast<ObstacleBox*>(OBSTACLE_MANAGER->GetObstacle());
			if (box == nullptr)
			{
				return;
			}
            box->SetPosition(Vector3(depth, -1000.0f + (200.0f * (one)) + (size * 50.0f), 2000.0f - (200.0f * (ten + 1)) + (size * 50.0f)));
            box->UseObstacle();
			box->SetScale(size * 100.0f);
            SetPosition(Vector3(depth, -0.0f, 0.0f));
        }
    }
}
