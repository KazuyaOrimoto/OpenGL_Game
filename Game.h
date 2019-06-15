#pragma once
#include "SDL.h"
#include <unordered_map>
#include <vector>
#include <string>

class FPS;
class GameObject;
class Texture;
class Ship;
class Shader;
class SpriteComponent;
class VertexArray;
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
	///**
	//@brief  �X�v���C�g�̒ǉ�
	//@param	�ǉ�����SpriteComponent�N���X�̃|�C���^
	//*/
 //   void AddSprite(SpriteComponent* argSprite);
	///**
	//@brief  �X�v���C�g�̍폜
	//@param	�폜����SpriteComponent�N���X�̃|�C���^
	//*/
	//void RemoveSprite(SpriteComponent* argSprite);

	///**
	//@brief  �e�N�X�`���̎擾
	//@param	�擾�������e�N�X�`���̃t�@�C����
	//@return �e�N�X�`���̃|�C���^
	//*/
	//Texture* GetTexture(const std::string& argFileName);

    class Renderer* GetRenderer() { return renderer; }


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
	@brief  �V�F�[�_�[�̓ǂݍ���
	*/
	bool LoadShaders();

	/**
	@brief  Sprite�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
	*/
	void CreateSpriteVerts();

	/**
	@brief  �Q�[���ɕK�v�ȃf�[�^�̃��[�h
	*/
	void LoadData();

	/**
	@brief  �Q�[���Ŏg�����f�[�^�̉��
	*/
	void UnloadData();

	FPS*            fps;

	//�Q�[���I�u�W�F�N�g�̃|�C���^�̉ϒ��R���e�i
	std::vector<GameObject*> gameObjects;
	//Update���ɒǉ����ꂽ�Q�[���I�u�W�F�N�g�̃|�C���^���ꎞ�I�ɕۑ�����ϒ��R���e�i
	std::vector<GameObject*> pendingGameObjects;
	////�X�v���C�g�R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	//std::vector<SpriteComponent*> sprites;
	////�t�@�C�����Ńe�N�X�`�����擾���邽�߂̉ϒ��R���e�i
	//std::unordered_map<std::string, Texture*>textures;

    Renderer* renderer;

	//�Q�[���𑱂��邩�ǂ���
    bool isRunning;
	//Update�����ǂ���
	bool updatingGameObject;

};

