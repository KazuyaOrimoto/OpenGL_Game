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
#include "GameOverLogo.h"
#include "GameClearLogo.h"
#include "TitlePlayer.h"

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
	case GameOver:
		StartGameOverScene();
		break;
	case GameClear:
		StartGameClearScene();
		break;
	default:
		break;
	}
	needChangeScene = false;
}

void SceneManager::StartPlayScene()
{
	RENDERER->SetScreenMat(Vector3(1.0f, 1.0f, 1.0f), Quaternion::Identity, Vector3(0.0f, 0.0f, 0.0f));

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
	new TitlePlayer();
	RENDERER->SetScreenMat(Vector3(1.0f,1.0f,1.0f),Quaternion::Identity,Vector3(0.0f,-0.0f,0.0f));
}

void SceneManager::StartGameOverScene()
{
	new GameOverLogo();
}

void SceneManager::StartGameClearScene()
{
	new GameClearLogo();
}
