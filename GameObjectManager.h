                                                                                      #pragma once
#define GAME_OBJECT_MANAGER GameObjectManager::GetInstance()

#include "SDL.h"
#include <unordered_map>
#include <vector>
#include <string>
#include "GameObject.h"

class GameObject;
struct InputState;

class GameObjectManager
{
public:
	static GameObjectManager* GetInstance() { return manager; }
	static void CreateInstance();
	static void DeleteInstance();

	/**
	@brief  ゲームオブジェクトのアップデート処理
	*/
	void UpdateGameObject(float argDeltaTime);

	/**
	@brief  ゲームオブジェクトの入力処理
	*/
	void ProcessInput(const InputState& state);

	/**
	@brief  ゲームオブジェクトの追加
	@param	追加するGameObjectクラスのポインタ
	*/
	void AddGameObject(GameObject* argObj);

	/**
	@brief  ゲームオブジェクトの削除
	@param	削除するGameObjectクラスのポインタ
	*/
	void RemoveGameObject(GameObject* argObj);

	GameObject* FindGameObject(Tag tag);
	std::vector<GameObject*> FindGameObjects(Tag tag);

private:
	GameObjectManager();
	~GameObjectManager();

	static GameObjectManager* manager;

	//ゲームオブジェクトのポインタの可変長コンテナ
	std::vector<GameObject*> gameObjects;
	//Update中に追加されたゲームオブジェクトのポインタを一時的に保存する可変長コンテナ
	std::vector<GameObject*> pendingGameObjects;

	//Update中かどうか
	bool updatingGameObject;


};
