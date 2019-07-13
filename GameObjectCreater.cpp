#include "GameObjectCreater.h"
#include "GameObject.h"
#include "PlayerObject.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "BoxObject.h"

GameObjectCreater* GameObjectCreater::creater = nullptr;

void GameObjectCreater::CreateInstance()
{
    if (creater == nullptr)
    {
        creater = new GameObjectCreater();
    }
}

void GameObjectCreater::DeleteInstance()
{
    if (creater != nullptr)
    {
        delete creater;
        creater = nullptr;
    }
}

GameObjectCreater::GameObjectCreater()
{
}

GameObjectCreater::~GameObjectCreater()
{
}

void GameObjectCreater::PlayerAndWallCreate(Game& game)
{
    // Camera actor
    GameObject* mCameraActor = new PlayerObject(&game);
    GameObject* box = new BoxObject(&game);


    for (int i = 0; i < 50; i++)
    {
        GameObject* a = new GameObject(&game);
        a->SetScale(1000.0f);
        a->SetPosition(Vector3(i*2000.0f, 0.0f, 0.0f));
        MeshComponent* mc = new MeshComponent(a);
        mc->SetMesh(game.GetRenderer()->GetMesh("Assets/Wall.gpmesh"));
    }


}
