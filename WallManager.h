#pragma once
#include <vector>

#define WALL_MANAGER WallManager::GetInstance()
class GameObject;
class PlayerObject;

class WallManager
{
public:
	static WallManager* GetInstance() { return wallManager; }
	static void CreateInstance();
	static void DeleteInstance();

	void UpdateWall();

	/**
	@brief  Wallオブジェクトの追加
	@param	追加するGameObjectクラスのポインタ
	*/
	void AddWallObject(GameObject* argObj);

	/**
	@brief  Wallオブジェクトの削除
	@param	削除するGameObjectクラスのポインタ
	*/
	void RemoveWallObject(GameObject* argObj);

	void AddPlayer(PlayerObject* argPlayer) { player = argPlayer; }
	void RemovePlayer() { player = nullptr; }

private:
	WallManager();
	~WallManager();
	static WallManager* wallManager;

	PlayerObject* player;
	//ゲームオブジェクトのポインタの可変長コンテナ
	std::vector<GameObject*> wallObjects;

};

