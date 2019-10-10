#pragma once

#define SCENE_MANAGER SceneManager::GetInstance()

enum SceneName
{
	Title,
	Play,
	Result
};

class SceneBase;

class SceneManager
{
public:
	/**
	@brief  インスタンスを取得する
	@return SceneManagerクラスのインスタンス
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
	*/
	void Initialize();
	/**
	@brief  終了処理
	*/
	void Shutdown();

    void ChangeScene(SceneName _name);

private:

	SceneManager();
	~SceneManager();

	static SceneManager* sceneManager;
    SceneBase* nowScene;
    
};

