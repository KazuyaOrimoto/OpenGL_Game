#pragma once
#include <vector>

class FPS;
class GameObject;
struct SDL_Window;
struct SDL_Renderer;

class Game
{
public:
	Game();
	~Game();
	/**
	@brief  初期化処理
	@return true : 成功 , false : 失敗
	*/
	bool Initialize();
	/**
	@brief  終了処理
	*/
	void Termination();
	/**
	@brief  ゲームループ
	*/
	void GameLoop();
	
	/**
	@brief  ゲームオブジェクトの追加
	@param	追加するGameObjectクラスのポインタ
	*/
	void AddGameObject(GameObject* argObj);
	/**
	@brief  ゲームオブジェクトの削除
	@param	削除するGameObjectクラスのポインタ
	*/
	void RemoveGameObject(GameObject* argObj);



private:
	/**
	@brief  入力関連の処理
	*/
    void ProcessInput();
	/**
	@brief  描画関連の処理
	*/
    void GenerateOutput();

	SDL_Window	* window;
	SDL_Renderer* renderer;
	FPS			*fps;

	std::vector<GameObject*> gameObjects;				//ゲームオブジェクトのポインタの可変長コンテナ
	std::vector<GameObject*> pendingGameObjects;		//Update中に追加されたゲームオブジェクトのポインタを一時的に保存する可変長コンテナ

    bool isRunning;										//ゲームを続けるかどうか
	bool updatingGameObject;							//Update中かどうか

};

