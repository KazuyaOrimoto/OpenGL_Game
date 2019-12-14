#pragma once

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
	bool Initialize();

	/**
	@brief  終了処理
	*/
	void Shutdown();


	void Update();

	void Draw();

private:
	static imguiManager* imgui;
	struct ImVec4 clearColor;
	bool show_demo_window;
	bool show_another_window;
	struct SDL_Window* window;
};

