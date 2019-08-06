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
	@brief  Wall�I�u�W�F�N�g�̒ǉ�
	@param	�ǉ�����GameObject�N���X�̃|�C���^
	*/
	void AddWallObject(GameObject* argObj);

	/**
	@brief  Wall�I�u�W�F�N�g�̍폜
	@param	�폜����GameObject�N���X�̃|�C���^
	*/
	void RemoveWallObject(GameObject* argObj);

	void AddPlayer(PlayerObject* argPlayer) { player = argPlayer; }
	void RemovePlayer() { player = nullptr; }

private:
	WallManager();
	~WallManager();
	static WallManager* wallManager;

	PlayerObject* player;
	//�Q�[���I�u�W�F�N�g�̃|�C���^�̉ϒ��R���e�i
	std::vector<GameObject*> wallObjects;

};

