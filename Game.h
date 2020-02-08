//=============================================================================
//	@file	Game.h
//	@brief	ゲーム全体の進行をまとめる
//	@autor	居本 和哉
//	@date	2019/10/3
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	プリプロセッサ
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "SDL.h"
#include <unordered_map>
#include <vector>
#include <string>


//-----------------------------------------------------------------------------
//	@brief	前方宣言
//-----------------------------------------------------------------------------
class FPS;
class GameObject;
class InputSystem;
class SceneBase;

//-----------------------------------------------------------------------------
//	@brief	Gameクラス
//-----------------------------------------------------------------------------
class Game final
{
public:

//===================== パブリック関数 ======================//

	Game(int _argc, char** _argv);
	~Game();

    /**
    @brief	初期化処理
    @return true : 成功, false : 失敗
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

	enum GameState
	{
		EGameplay,
		EPaused,
		EQuit
	};

	static GameState GetState() { return gameState; }
	static void SetState(GameState _state) { gameState = _state; }

	

private:
//===================== プライベート関数 ======================//

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
	@brief   ロードしたデータの解放
	*/
	void UnloadData();

	void HandleKeyPress(int key);

	/**
	@brief  ゲームオブジェクトのアップデート処理
	*/
	friend void UpdateGameObjects(float _deltaTime);

	/**
	@brief  ゲームオブジェクトの入力処理
	*/
	friend void ProcessInputs(const struct InputState& _state);

//===================== メンバ変数 ======================//

	FPS*				fps;				// FPS計測クラス
	InputSystem*		inputSystem;		// 入力管理クラス
	static GameState	gameState;				// ゲームの状態
	int argc;
	char** argv;
};

