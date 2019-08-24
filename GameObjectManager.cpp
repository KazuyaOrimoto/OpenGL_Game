#include "GameObjectManager.h"
#include "GameObject.h"
#include "InputSystem.h"

GameObjectManager* GameObjectManager::manager = nullptr;

void GameObjectManager::CreateInstance()
{
	if (manager == nullptr)
	{
		manager = new GameObjectManager();
	}
}

void GameObjectManager::DeleteInstance()
{
	if (manager != nullptr)
	{
		delete manager;
        manager = nullptr;
	}
}

/**
@brief  ゲームオブジェクトのアップデート処理
*/
void GameObjectManager::UpdateGameObject(float argDeltaTime)
{
	updatingGameObject = true;
	for (auto gameObject : gameObjects)
	{
		gameObject->Update(argDeltaTime);
	}
	updatingGameObject = false;

	for (auto pending : pendingGameObjects)
	{
		pending->ComputeWorldTransform();
		gameObjects.emplace_back(pending);
	}
	pendingGameObjects.clear();
}

void GameObjectManager::ProcessInput(const InputState& state)
{
	updatingGameObject = true;
	for (auto gameObject : gameObjects)
	{
		gameObject->ProcessInput(state);
	}
	updatingGameObject = false;
}

/**
@brief  ゲームオブジェクトの追加
@param	追加するGameObjectクラスのポインタ
*/
void GameObjectManager::AddGameObject(GameObject* argObj)
{
	if (updatingGameObject)
	{
		pendingGameObjects.emplace_back(argObj);
	}
	else
	{
		gameObjects.emplace_back(argObj);
	}
}

/**
@brief  ゲームオブジェクトの削除
@param	削除するGameObjectクラスのポインタ
*/
void GameObjectManager::RemoveGameObject(GameObject * argObj)
{
	auto iter = std::find(pendingGameObjects.begin(), pendingGameObjects.end(), argObj);
	if (iter != pendingGameObjects.end())
	{
		std::iter_swap(iter, pendingGameObjects.end() - 1);
		pendingGameObjects.pop_back();
	}

	iter = std::find(gameObjects.begin(), gameObjects.end(), argObj);
	if (iter != gameObjects.end())
	{
		std::iter_swap(iter, gameObjects.end() - 1);
		gameObjects.pop_back();
	}
}

GameObject * GameObjectManager::FindGameObject(Tag tag)
{
	for (auto itr : gameObjects)
	{
		if (itr->GetTag() == tag)
		{
			return itr;
		}
	}
	return nullptr;
}

std::vector<GameObject*> GameObjectManager::FindGameObjects(Tag tag)
{
	std::vector<GameObject*> ret;
	for (auto itr : gameObjects)
	{
		if (itr->GetTag() == tag)
		{
			ret.push_back(itr);
		}
	}
	return ret;
}


GameObjectManager::GameObjectManager()
: updatingGameObject(false)
{
}


GameObjectManager::~GameObjectManager()
{
	while (!gameObjects.empty())
	{
		delete gameObjects.back();
	}
}
