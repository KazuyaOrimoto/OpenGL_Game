#pragma once

enum SceneName
{
	Title,
	Play,
	Result
};

class SceneManager
{
public:
	/**
	@brief  �C���X�^���X���擾����
	@return Renderer�N���X�̃C���X�^���X
	*/
	static SceneManager* GetInstance() { return sceneManager; }

	/**
	@brief  �C���X�^���X���쐬����
	*/
	static void CreateInstance();

	/**
	@brief  �C���X�^���X���폜����
	*/
	static void DeleteInstance();

	/**
	@brief  ����������
	@return true : ���� , false : ���s
	*/
	void Initialize();
	/**
	@brief  �I������
	*/
	void Shutdown();


private:

	SceneManager();
	~SceneManager();

	static SceneManager* sceneManager;
};

