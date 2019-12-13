#pragma once

#define IMGUI_MANAGER imguiManager::GetInstance()

class imguiManager
{
public:
	imguiManager();
	~imguiManager();

	/**
	@brief  �C���X�^���X���擾����
	@return imguiManager�N���X�̃C���X�^���X
	*/
	static imguiManager* GetInstance() { return imgui; }

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
	bool Initialize();


private:
	static imguiManager* imgui;
};

