#pragma once
#include "SDL.h"
#include <unordered_map>
#include <vector>
#include <string>

class FPS;
class GameObject;
class InputSystem;

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
	InputSystem* inputSystem;

	//�Q�[���𑱂��邩�ǂ���
    bool isRunning;

};

