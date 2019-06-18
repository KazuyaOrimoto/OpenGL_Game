#pragma once
#include "SDL.h"
#include <unordered_map>
#include <vector>
#include <string>

class FPS;
class GameObject;
class Renderer;

class Game
{
public:
	Game();
	~Game();
	/**
	@brief  ����������
	@return true : ���� , false : ���s
	*/
	bool Initialize();
	/**
	@brief  �I������
	*/
	void Termination();
	/**
	@brief  �Q�[�����[�v
	*/
	void GameLoop();
	
	/**
	@brief  �Q�[���I�u�W�F�N�g�̒ǉ�
	@param	�ǉ�����GameObject�N���X�̃|�C���^
	*/
	void AddGameObject(GameObject* argObj);
	/**
	@brief  �Q�[���I�u�W�F�N�g�̍폜
	@param	�폜����GameObject�N���X�̃|�C���^
	*/
	void RemoveGameObject(GameObject* argObj);

	// Getter / Setter
    Renderer* GetRenderer() { return renderer; }

private:
	/**
	@brief  ���͊֘A�̏���
	*/
    void ProcessInput();
	/**
	@brief  �`��֘A�̏���
	*/
    void GenerateOutput();

	/**
	@brief  �Q�[���̃A�b�v�f�[�g����
	*/
	void UpdateGame();

	/**
	@brief  �Q�[���ɕK�v�ȃf�[�^�̃��[�h
	*/
	void LoadData();

	/**
	@brief  �Q�[���Ŏg�����f�[�^�̉��
	*/
	void UnloadData();

	//�Q�[���I�u�W�F�N�g�̃|�C���^�̉ϒ��R���e�i
	std::vector<GameObject*> gameObjects;
	//Update���ɒǉ����ꂽ�Q�[���I�u�W�F�N�g�̃|�C���^���ꎞ�I�ɕۑ�����ϒ��R���e�i
	std::vector<GameObject*> pendingGameObjects;

	// �N���X�̃C���X�^���X

	FPS* fps;
    Renderer* renderer;

	//�Q�[���𑱂��邩�ǂ���
    bool isRunning;
	//Update�����ǂ���
	bool updatingGameObject;

};

