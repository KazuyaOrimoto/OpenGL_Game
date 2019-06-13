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
struct SDL_Window;
struct SDL_Renderer;

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
	/**
	@brief  �X�v���C�g�̒ǉ�
	@param	�ǉ�����SpriteComponent�N���X�̃|�C���^
	*/
    void AddSprite(SpriteComponent* argSprite);
	/**
	@brief  �X�v���C�g�̍폜
	@param	�폜����SpriteComponent�N���X�̃|�C���^
	*/
	void RemoveSprite(SpriteComponent* argSprite);

	Texture* GetTexture(const std::string& argFileName);


private:
	/**
	@brief  ���͊֘A�̏���
	*/
    void ProcessInput();
	/**
	@brief  �`��֘A�̏���
	*/
    void GenerateOutput();

	void UpdateGame();

	bool LoadShaders();
	void CreateSpriteVerts();

	void LoadData();
	void UnloadData();

	FPS*            fps;
	SDL_Window*     window;
    SDL_GLContext   context;

	//�Q�[���I�u�W�F�N�g�̃|�C���^�̉ϒ��R���e�i
	std::vector<GameObject*> gameObjects;
	//Update���ɒǉ����ꂽ�Q�[���I�u�W�F�N�g�̃|�C���^���ꎞ�I�ɕۑ�����ϒ��R���e�i
	std::vector<GameObject*> pendingGameObjects;
	//�X�v���C�g�R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<SpriteComponent*> sprites;

	std::unordered_map<std::string, Texture*>textures;

	//�Q�[���𑱂��邩�ǂ���
    bool isRunning;
	//Update�����ǂ���
	bool updatingGameObject;

	Shader* spriteShader;
	VertexArray* spriteVerts;

	Ship* ship;

};

