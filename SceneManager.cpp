#include "SceneManager.h"
#include "SceneBase.h"
#include "TitleScene.h"
#include "PlayScene.h"


SceneManager* SceneManager::sceneManager = nullptr;

void SceneManager::CreateInstance()
{
	if (sceneManager == nullptr)
	{
		sceneManager = new SceneManager();
	}
}

void SceneManager::DeleteInstance()
{
	if (sceneManager != nullptr)
	{
		delete sceneManager;
		sceneManager = nullptr;
	}
}

void SceneManager::Initialize()
{
    nowScene = SceneBase::StartGame();
}

void SceneManager::Shutdown()
{
}

void SceneManager::ChangeScene(SceneName _name)
{
    delete nowScene;
    nowScene = nullptr;
    switch (_name)
    {
    case Title:
        nowScene = new TitleScene();
        break;
    case Play:
        nowScene = new PlayScene();
        break;
    //case Result:
    //    nowScene = new TitleScene();
        //break;
    default:
        break;
    }
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}
