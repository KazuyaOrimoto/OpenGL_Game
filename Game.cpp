//=============================================================================
//	@file	Game.cpp
//	@brief	ゲーム全体の進行をまとめる
//	@autor	居本 和哉
//	@date	2019/10/3
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Game.h"
#include "SDL.h"
#include <glew.h>
#include <algorithm>
#include "FPS.h"
#include "Renderer.h"
#include "InputSystem.h"
#include "PhysicsWorld.h"
#include "GameObjectManager.h"
#include "GameObjectCreater.h"
#include "ObstacleManager.h"
#include "SceneManager.h"

/**
@brief  コンストラクタ
*/
Game::Game()
	: fps(nullptr)
    , isRunning(true)
{
}

/**
@brief  デストラクタ
*/
Game::~Game()
{
}

/**
@brief  初期化処理
@return true : 成功 , false : 失敗
*/
bool Game::Initialize()
{
	//SDLの初期化
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	//レンダラーの初期化
	Renderer::CreateInstance();
	if (!RENDERER->Initialize(1024.0f, 768.0f))
	{
		SDL_Log("Failed to initialize renderer");
		Renderer::DeleteInstance();
		return false;
	}

    //当たり判定用クラスの初期化
	PhysicsWorld::CreateInstance();

    //入力管理クラスの初期化
	inputSystem = new InputSystem();
	if (!inputSystem->Initialize())
	{
		SDL_Log("Failed to initialize input system");
		return false;
	}

	//FPS管理クラスの初期化
	fps = new FPS();

    //ゲームオブジェクト管理クラスの初期化
    GameObjectManager::CreateInstance();
    //ゲームオブジェクト生成クラスの初期化
    GameObjectCreater::CreateInstance();
	//障害物管理クラスの初期化
    ObstacleManager::CreateInstance();
    //シーン管理クラスの初期化
    SceneManager::CreateInstance();
    SCENE_MANAGER->Initialize();

	return true;
}

/**
@brief  終了処理
*/
void Game::Termination()
{
    //データのアンロード
	UnloadData();
    //シングルトンクラスの解放処理
    GameObjectManager::DeleteInstance();
    GameObjectCreater::DeleteInstance();
	Renderer::DeleteInstance();
	PhysicsWorld::DeleteInstance();
	ObstacleManager::DeleteInstance();
    SceneManager::DeleteInstance();
    //クラスの解放処理
    delete fps;
    delete inputSystem;
    //サブシステムの終了
	SDL_Quit();
}

/**
@brief  ゲームループ
*/
void Game::GameLoop()
{
	while (isRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
		fps->Update();
	}
}

/**
@brief   ロードしたデータの解放
*/
void Game::UnloadData()
{
	if (RENDERER != nullptr)
	{
		RENDERER->UnloadData();
		RENDERER->Shutdown();
	}
}

/**
@brief  入力関連の処理
*/
void Game::ProcessInput()
{
	inputSystem->PrepareForUpdate();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEWHEEL:
			inputSystem->ProcessEvent(event);
			break;
		default:
			break;
		}
	}

	inputSystem->Update();
	const InputState& state = inputSystem->GetState();

	if (state.Keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == Released)
	{
		isRunning = false;
	}

	GAME_OBJECT_MANAGER->ProcessInput(state);
}

/**
@brief  描画関連の処理
*/
void Game::GenerateOutput()
{
	RENDERER->Draw();
}

/**
@brief  ゲームのアップデート処理
*/
void Game::UpdateGame()
{
	float deltaTime = fps->GetDeltaTime();
	
	GAME_OBJECT_MANAGER->UpdateGameObject(deltaTime);
}