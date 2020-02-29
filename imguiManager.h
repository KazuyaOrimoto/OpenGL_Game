//=============================================================================
//	@file	imguiManager.h
//	@brief	imguiを使うための管理クラス
//	@autor	居本 和哉
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
	@brief  インスタンスを取得する
	@return imguiManagerクラスのインスタンス
	*/
	static imguiManager* GetInstance() { return imgui; }

	/**
	@brief  インスタンスを作成する
	*/
	static void CreateInstance();

	/**
	@brief  インスタンスを削除する
	*/
	static void DeleteInstance();

	/**
	@brief  初期化処理
	@return true : 成功 , false : 失敗
	*/
	bool Initialize(SDL_Window* _window, SDL_GLContext _context, float _screenWidth, float _screenHeight);

	/**
	@brief  終了処理
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
	//スクリーンの横幅
	float screenWidth;
	//スクリーンの縦幅
	float screenHeight;
	char str[128];
};


#endif // _DEBUG

