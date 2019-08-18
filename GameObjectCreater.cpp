#include "GameObjectCreater.h"
#include "GameObject.h"
#include "PlayerObject.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "BoxObject.h"
#include "ObstacleObject.h"
#include "WallObject.h"
#include "ObstacleBox.h"

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

void GameObjectCreater::PlayerAndWallCreate(Game* game)
{
	GameObject* mCameraActor = new PlayerObject(game);

	ObstacleBox* box;
	for (int i = 0; i < 100; i++)
	{
		box = new ObstacleBox(game);
	}

	for (int i = 0; i < 20; i++)
	{
		ObstacleObject* obstacle = new ObstacleObject(game,i);
	}


	for (int i = 0; i < 20; i++)
	{
		GameObject* wall = new WallObject(game, i);
	}
}
