#include "SceneManager.h"
#include "GameObject.h"
#include "PlayerObject.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "BoxObject.h"
#include "ObstacleObject.h"
#include "WallObject.h"
#include "ObstacleBox.h"
#include "Ship.h"
#include "Titlelogo.h"
#include "ResultLogo.h"
#include "BoostItem.h"

SceneName SceneManager::scene = SceneName::NONE;
bool SceneManager::needChangeScene = false;

void SceneManager::ChangeScene(SceneName _name)
{
	scene = _name;
	needChangeScene = true;
}

void SceneManager::SceneUpdate()
{
	if (!needChangeScene)
	{
		return;
	}
	GameObject::ResetGameObject();
	switch (scene)
	{
	case Title:
		StartTitleScene();
		break;
	case Play:
		StartPlayScene();
		break;
	case Result:
		StartResultScene();
		break;
	default:
		break;
	}
	needChangeScene = false;
}

void SceneManager::StartPlayScene()
{
	GameObject* mCameraActor = new PlayerObject();

	std::string name = typeid(mCameraActor).name();

	ObstacleBox* box;
	for (int i = 0; i < 500; i++)
	{
		box = new ObstacleBox();
	}

	BoostItem* item;
	for (int i = 0; i < 50; i++)
	{
		item = new BoostItem();
	}

	for (int i = 0; i < StaticObstacle::ObstacleMaxNum; i++)
	{
		ObstacleObject* obstacle = new ObstacleObject(i);
	}

	for (int i = 0; i < 10; i++)
	{
		GameObject* wall = new WallObject(i);
	}
}

void SceneManager::StartTitleScene()
{
	new Titlelogo();
}

void SceneManager::StartResultScene()
{
	new ResultLogo();
}

