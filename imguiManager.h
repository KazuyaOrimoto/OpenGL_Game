//=============================================================================
//	@file	imguiManager.h
//	@brief	imgui���g�����߂̊Ǘ��N���X
//	@autor	���{ �a��
//	@date	2020/02/29
//=============================================================================

#ifdef _DEBUG
#define USE_IMGUI

#pragma once

#include <SDL.h>
#include "imgui/imgui.h"



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
	bool Initialize(SDL_Window* _window, SDL_GLContext _context, float _screenWidth, float _screenHeight);

	/**
	@brief  �I������
	*/
	void Shutdown();

	void SetSDLEvent(SDL_Event _event) { event = _event; }

	void Update();

	void Draw();

	void ShowGameObjects();

	void ShowRenderer();

private:
	static imguiManager* imgui;
	struct ImVec4 clearColor;
	bool show_demo_window;
	bool showGameObjectsWindow;
	SDL_Window* window;
	SDL_Event event;
	//�X�N���[���̉���
	float screenWidth;
	//�X�N���[���̏c��
	float screenHeight;
	char str[128];
};


#endif // _DEBUG

