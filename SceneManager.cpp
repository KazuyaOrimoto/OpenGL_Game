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

void SceneManager::ChangeScene(SceneName _name)
{
	GameObject::ResetGameObject();
    switch (_name)
    {
    case Title:
		StartTitleScene();
        break;
    case Play:
		StartPlayScene();
        break;
    default:
        break;
    }
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

	for (int i = 0; i < StaticObstacle::ObstacleMaxNum; i++)
	{
		ObstacleObject* obstacle = new ObstacleObject(i);
	}

	for (int i = 0; i < 20; i++)
	{
		GameObject* wall = new WallObject(i);
	}
}

void SceneManager::StartTitleScene()
{
	new Titlelogo();
}
