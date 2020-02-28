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
#include "ObstacleManager.h"
#include "SceneManager.h"
#include <string>
#include "GameObject.h"
#include "SceneManager.h"
#include "imguiManager.h"
#include "EffekseerManager.h"

//-----------------------------------------------------------------------------
//	@brief	staticメンバ変数の初期化
//-----------------------------------------------------------------------------
Game::GameState Game::gameState = GameState::EGameplay;

/**
@brief  コンストラクタ
*/
Game::Game()
	// メンバ変数の初期化
	: fps(nullptr)
	, inputSystem(nullptr)
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
	// SDLの初期化
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER | SDL_INIT_TIMER) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Rendererクラスのインスタンスの作成
	Renderer::CreateInstance();
	// Rendererの初期化
	if (!RENDERER->Initialize(1920.0f,1080.0f))
	{
		SDL_Log("Failed to initialize renderer");
		Renderer::DeleteInstance();
		return false;
	}

	// Effekseerクラスのインスタンスの作成
	EffekseerManager::CreateInstance();
	// Effekseerクラスの初期化
	EFFECT_MANAGER->Initialize();

	// Rendererの必要なデータのロード
	if (!RENDERER->LoadData())
	{
		SDL_Log("Failed to initialize renderer");
		Renderer::DeleteInstance();
		return false;
	}

#ifdef USE_IMGUI
	// ImguiManagerクラスのインスタンスの作成
	imguiManager::CreateInstance();
	//ImguiManagerの初期化に失敗した場合
	if (!IMGUI_MANAGER->Initialize(RENDERER->GetSDLWindow(), RENDERER->GetContext(), RENDERER->GetScreenWidth(), RENDERER->GetScreenHeight()))
	{
		SDL_Log("Failed to initialize imgui");
		return false;
	}
#endif // USE_IMGUI

	fps = new FPS();
	inputSystem = new InputSystem();
	// InputSystemの初期化に失敗した場合
	if (!inputSystem->Initialize())
	{
		SDL_Log("Failed to initialize input system");
		return false;
	}

    // PhysicsWorldクラスのインスタンスの作成
	PhysicsWorld::CreateInstance();

	// ObstacleManagerクラスのインスタンスの作成
    ObstacleManager::CreateInstance();

	// 最初のシーンをTitleに設定
	SceneManager::ChangeScene(SceneName::Title);

	return true;
}

/**
@brief  終了処理
*/
void Game::Termination()
{
    // データのアンロード
	UnloadData();
	// Rendererクラスのインスタンスの削除
	Renderer::DeleteInstance();
	// PhysicsWorldクラスのインスタンスの削除
	PhysicsWorld::DeleteInstance();
	// ObstacleManagerクラスのインスタンスの削除
	ObstacleManager::DeleteInstance();
	// EffekseerManagerクラスのインスタンスの削除
	EffekseerManager::DeleteInstance();
#ifdef USE_IMGUI
	// imguiManagerクラスのインスタンスの削除
	imguiManager::DeleteInstance();
#endif // USE_IMGUI
    delete fps;
    delete inputSystem;
    // サブシステムの終了
	SDL_Quit();
}

/**
@brief  ゲームループ
*/
void Game::GameLoop()
{
	// ゲームのメインループを継続するか
	while (gameState != EQuit)
	{
		SceneManager::SceneUpdate();
		ProcessInput();
		UpdateGame();
		GenerateOutput();
		fps->Update();
#ifdef USE_IMGUI
		IMGUI_MANAGER->Update();
#endif // USE_IMGUI
	}
}

/**
@brief  ロードしたデータの解放
*/
void Game::UnloadData()
{
	GameObject::DeleteAllGameObjects();
	if (RENDERER != nullptr)
	{
		RENDERER->UnloadData();
		RENDERER->Shutdown();
	}
#ifdef USE_IMGUI
	if (IMGUI_MANAGER != nullptr)
	{
		IMGUI_MANAGER->Shutdown();
	}
#endif // USE_IMGUI
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
			gameState = GameState::EQuit;
			break;
		default:
			break;
		}
	}
	inputSystem->Update();
#ifdef USE_IMGUI
	IMGUI_MANAGER->SetSDLEvent(event);
#endif // USE_IMGUI
	const InputState& state = inputSystem->GetState();

	if (gameState == Game::EGameplay)
	{
		ProcessInputs(state);
	}
	//Escapeを押された場合
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Pressed)
	{
		gameState = Game::EQuit;
	}
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
	
	UpdateGameObjects(deltaTime);
}

/**
@brief  ゲームオブジェクトのアップデート処理
*/
void UpdateGameObjects(float _deltaTime)
{
	if (Game::GetState() == Game::GameState::EGameplay)
	{
		GameObject::updatingGameObject = true;
		for (auto gameObject : GameObject::gameObjects)
		{
			gameObject->Update(_deltaTime);
		}
		GameObject::updatingGameObject = false;

		//Update中に追加されたGameObjectの処理
		for (auto pending : GameObject::pendingGameObjects)
		{
			pending->ComputeWorldTransform();
			GameObject::gameObjects.emplace_back(pending);
		}
		GameObject::pendingGameObjects.clear();
	}
}

/**
@brief  ゲームオブジェクトの入力処理
*/
void ProcessInputs(const InputState & _state)
{
	GameObject::updatingGameObject = true;
	for (auto gameObject : GameObject::gameObjects)
	{
		gameObject->ProcessInput(_state);
	}
	GameObject::updatingGameObject = false;
}


