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
#include "UIManager.h"
#include "PauseMenu.h"
#include "UIScreen.h"
#include <SDL_ttf.h>
#include <string>
#include "GameObject.h"
#include "SceneManager.h"
#include "imguiManager.h"
#include "EffekseerManager.h"

Game::GameState Game::gameState = GameState::EGameplay;

/**
@brief  コンストラクタ
*/
Game::Game()
	// メンバ変数の初期化
	: fps(nullptr)
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


	// レンダラーの初期化
	Renderer::CreateInstance();
	if (!RENDERER->Initialize(1600.0f, 900.0f))
	{
		SDL_Log("Failed to initialize renderer");
		Renderer::DeleteInstance();
		return false;
	}

	EffekseerManager::CreateInstance();
	EFFECT_MANAGER->InitEffekseer();

	if (!RENDERER->LoadData())
	{
		SDL_Log("Failed to initialize renderer");
		Renderer::DeleteInstance();
		return false;
	}

	imguiManager::CreateInstance();
	if (!IMGUI_MANAGER->Initialize(RENDERER->GetSDLWindow(),RENDERER->GetContext(),RENDERER->GetScreenWidth(),RENDERER->GetScreenHeight()))
	{
		SDL_Log("Failed to initialize imgui");
		return false;
	}

    // 入力管理クラスの初期化
	inputSystem = new InputSystem();
	if (!inputSystem->Initialize())
	{
		SDL_Log("Failed to initialize input system");
		return false;
	}

	// Initialize SDL_ttf
	if (TTF_Init() != 0)
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}

    // 当たり判定用クラスの初期化
	PhysicsWorld::CreateInstance();

	// FPS管理クラスの初期化
	fps = new FPS();


	// 障害物管理クラスの初期化
    ObstacleManager::CreateInstance();

	SceneManager::ChangeScene(SceneName::Play);

	UIManager::CreateInstance();



	UI_MANAGER->LoadText("Assets/English.gptext");

	return true;
}

/**
@brief  終了処理
*/
void Game::Termination()
{
    // データのアンロード
	UnloadData();
    // シングルトンクラスの解放処理
    //GameObjectManager::DeleteInstance();
	Renderer::DeleteInstance();
	PhysicsWorld::DeleteInstance();
	ObstacleManager::DeleteInstance();
	UIManager::DeleteInstance();
	imguiManager::DeleteInstance();
	EffekseerManager::DeleteInstance();
    // クラスの解放処理
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
		ProcessInput();
		UpdateGame();
		GenerateOutput();
		fps->Update();
		IMGUI_MANAGER->Update();
	}
}

/**
@brief  ロードしたデータの解放
*/
void Game::UnloadData()
{
	if (RENDERER != nullptr)
	{
		RENDERER->UnloadData();
		RENDERER->Shutdown();
	}

	if (IMGUI_MANAGER != nullptr)
	{
		IMGUI_MANAGER->Shutdown();
	}
}

void Game::HandleKeyPress(int key)
{
	switch (key)
	{
	case SDLK_ESCAPE:
		// Create pause menu
		new PauseMenu();
		break;
	case '1':
	{
		// Load English text
		UI_MANAGER->LoadText("Assets/English.gptext");
		break;
	}
	case '2':
	{
		// Load Russian text
		UI_MANAGER->LoadText("Assets/Russian.gptext");
		break;
	}
	default:
		break;
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
			gameState = GameState::EQuit;
			break;
		case SDL_KEYDOWN:
			if (!event.key.repeat)
			{
				if (gameState == GameState::EGameplay)
				{
					HandleKeyPress(event.key.keysym.sym);
				}
				else if (!UI_MANAGER->UIEmpty())
				{
					UI_MANAGER->HandleKeyPress(event.key.keysym.sym);
				}
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (gameState == EGameplay)
			{
				HandleKeyPress(event.button.button);
				inputSystem->ProcessEvent(event);
			}
			else if (!UI_MANAGER->UIEmpty())
			{
				UI_MANAGER->HandleKeyPress(event.button.button);
			}
			break;
		default:
			break;
		}
	}

	IMGUI_MANAGER->SetSDLEvent(event);

	inputSystem->Update();
	const InputState& state = inputSystem->GetState();

	if (gameState == Game::EGameplay)
	{
		ProcessInputs(state);
	}
	else if (!UI_MANAGER->UIEmpty())
	{
		UI_MANAGER->ProcessInput(state);
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
	
	UI_MANAGER->Update(deltaTime);
	UpdateGameObjects(deltaTime);
}

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

		for (auto pending : GameObject::pendingGameObjects)
		{
			pending->ComputeWorldTransform();
			GameObject::gameObjects.emplace_back(pending);
		}
		GameObject::pendingGameObjects.clear();
	}
}

void ProcessInputs(const InputState & _state)
{
	GameObject::updatingGameObject = true;
	for (auto gameObject : GameObject::gameObjects)
	{
		gameObject->ProcessInput(_state);
	}
	GameObject::updatingGameObject = false;
}