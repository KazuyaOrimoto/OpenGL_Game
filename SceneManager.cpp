#include "SceneManager.h"

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
	return;
}

void SceneManager::Shutdown()
{
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}
