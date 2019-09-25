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
#include "JumpingObject.h"

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

void GameObjectCreater::PlayerAndWallCreate(Game* _game)
{
	GameObject* mCameraActor = new PlayerObject(_game);

	ObstacleBox* box;
	for (int i = 0; i < 100; i++)
	{
		box = new ObstacleBox(_game);
	}
	for (int i = 0; i < 20; i++)
	{
		box = new JumpingObject(_game);
	}

	for (int i = 0; i < 50; i++)
	{
		ObstacleObject* obstacle = new ObstacleObject(_game,i);
	}

	for (int i = 0; i < 20; i++)
	{
		GameObject* wall = new WallObject(_game, i);
	}
}
