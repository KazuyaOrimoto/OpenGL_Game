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

rapidjson::Value& ObstacleObject::LoadMap(const std::string & argFileName)
{
    std::ifstream file(argFileName);
    if (!file.is_open())
    {
        SDL_Log("File not found: Map %s", argFileName.c_str());
        return;
    }

    std::stringstream fileStream;
    fileStream << file.rdbuf();
    std::string contents = fileStream.str();
    rapidjson::StringStream jsonStr(contents.c_str());
    rapidjson::Document doc;
    doc.ParseStream(jsonStr);

    rapidjson::Value& mapJson = doc["map"];
    return mapJson;
}

void ObstacleObject::CreateObstacle(float depth)
{
    rapidjson::Value& mapJson = LoadMap("MapData/map.json");
    int ten;
    int one;
    for (int i = 0; i < mapJson.Size(); i++)
    {
        if (mapJson[i].GetInt() == 2)
        {
            ten = i / 10;
            one = i % 10;
            ObstacleBox* box = dynamic_cast<ObstacleBox*>(OBSTACLE_MANAGER->GetObstacle());
            box->SetPosition(Vector3(depth, -0.0f, 150.0f));
            box->UseObstacle();
            SetPosition(Vector3(depth, -0.0f, 0.0f));
            player = GAME_OBJECT_MANAGER->FindGameObject(Tag::Player);
        }
    }

    ObstacleBox* box = dynamic_cast<ObstacleBox*>(OBSTACLE_MANAGER->GetObstacle());
    box->SetPosition(Vector3(depth, -0.0f, 150.0f));
    box->UseObstacle();

    box = OBSTACLE_MANAGER->GetObstacle();
    box->SetPosition(Vector3(depth, -0.0f, 1850.0f));
    box->UseObstacle();
    SetPosition(Vector3(depth, -0.0f, 0.0f));
}
