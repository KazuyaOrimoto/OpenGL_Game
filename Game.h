#pragma once
#include "SDL.h"
#include <unordered_map>
#include <vector>
#include <string>

class FPS;
class GameObject;
class Renderer;
class InputSystem;
class PhysicsWorld;

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
	@brief	�����_���[���擾����
	@param	Rederer�N���X�̃|�C���^
	*/
    Renderer* GetRenderer() { return renderer; }

    /**
    @brief	�A�^�������Ԃ��擾����
    @param	PhysicsWorld�N���X�̃|�C���^
    */
    PhysicsWorld* GetPhysicsWorld() { return physicsWorld; }

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
	@brief   ���[�h�����f�[�^�̉��
	*/
	void UnloadData();

	// �N���X�̃C���X�^���X

	FPS* fps;
    Renderer* renderer;
    PhysicsWorld* physicsWorld;
	InputSystem* inputSystem;

	//�Q�[���𑱂��邩�ǂ���
    bool isRunning;

};

