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
#include "WallManager.h"

Game::Game()
	: fps(nullptr)
    , isRunning(true)
{
}

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

	PhysicsWorld::CreateInstance();

	inputSystem = new InputSystem();
	//inputSystem->SetRelativeMouseMode(true);
	if (!inputSystem->Initialize())
	{
		SDL_Log("Failed to initialize input system");
		return false;
	}

	//FPS管理クラスの初期化
	fps = new FPS();

    GameObjectManager::CreateInstance();
    GameObjectCreater::CreateInstance();
	ObstacleManager::CreateInstance();
	WallManager::CreateInstance();

	LoadData();

	return true;
}

/**
@brief  終了処理
*/
void Game::Termination()
{
	UnloadData();
    GameObjectManager::DeleteInstance();
    GameObjectCreater::DeleteInstance();
	Renderer::DeleteInstance();
	PhysicsWorld::DeleteInstance();
	ObstacleManager::DeleteInstance();
	WallManager::DeleteInstance();
	SDL_Quit();
	delete fps;
	delete inputSystem;

}

/**
@brief  ゲームループ
*/
void Game::GameLoop()
{
	while (isRunning)
	{
		ProcessInput();
		fps->Update();
		UpdateGame();
		WALL_MANAGER->UpdateWall();
		PHYSICS->HitCheck();
		GenerateOutput();
	}
}

/**
@brief  ゲームに必要なデータのロード
*/
void Game::LoadData()
{
	  // Setup lights
	RENDERER->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.direction = Vector3(0.0f, -0.7f,-0.7f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

    GAME_OBJECT_CREATER->PlayerAndWallCreate(*this);
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