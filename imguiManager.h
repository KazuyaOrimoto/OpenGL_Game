#pragma once

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


private:
	static imguiManager* imgui;
};

