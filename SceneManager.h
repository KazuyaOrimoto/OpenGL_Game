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
	@brief  インスタンスを取得する
	@return Rendererクラスのインスタンス
	*/
	static SceneManager* GetInstance() { return sceneManager; }

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
	void Initialize();
	/**
	@brief  終了処理
	*/
	void Shutdown();


private:

	SceneManager();
	~SceneManager();

	static SceneManager* sceneManager;
};

