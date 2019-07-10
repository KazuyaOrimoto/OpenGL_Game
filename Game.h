#pragma once
#include "SDL.h"
#include <unordered_map>
#include <vector>
#include <string>

class FPS;
class GameObject;
class Renderer;
class InputSystem;
class PhysicsWorld;

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
	@brief	レンダラーを取得する
	@param	Redererクラスのポインタ
	*/
    Renderer* GetRenderer() { return renderer; }

    /**
    @brief	アタリ判定空間を取得する
    @param	PhysicsWorldクラスのポインタ
    */
    PhysicsWorld* GetPhysicsWorld() { return physicsWorld; }

private:
	/**
	@brief  入力関連の処理
	*/
    void ProcessInput();
	/**
	@brief  描画関連の処理
	*/
    void GenerateOutput();

	/**
	@brief  ゲームのアップデート処理
	*/
	void UpdateGame();

	/**
	@brief  ゲームに必要なデータのロード
	*/
	void LoadData();

	/**
	@brief   ロードしたデータの解放
	*/
	void UnloadData();

	// クラスのインスタンス

	FPS* fps;
    Renderer* renderer;
    PhysicsWorld* physicsWorld;
	InputSystem* inputSystem;

	//ゲームを続けるかどうか
    bool isRunning;

};

