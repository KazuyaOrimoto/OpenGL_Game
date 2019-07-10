#include "Game.h"
#include "SDL.h"
#include <glew.h>
#include <algorithm>
#include "FPS.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "Ship.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "PlaneObject.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "CameraObject.h"
#include "InputSystem.h"
#include "FPSGameObject.h"
#include "FollowCameraObject.h"
#include "SphereObject.h"
#include "PhysicsWorld.h"
#include "PlayerObject.h"
#include "GameObjectManager.h"

Game::Game()
	: fps(nullptr)
	, renderer(nullptr)

{
}

Game::~Game()
{
	delete fps;
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
	renderer = new Renderer(this);
	if (!renderer->Initialize(1024.0f, 768.0f))
	{
		SDL_Log("Failed to initialize renderer");
		delete renderer;
		renderer = nullptr;
		return false;
	}

	physicsWorld = new PhysicsWorld(this);

	inputSystem = new InputSystem();
	//inputSystem->SetRelativeMouseMode(true);
	if (!inputSystem->Initialize())
	{
		SDL_Log("Failed to initialize input system");
		return false;
	}

	//FPS管理クラスの初期化
	fps = new FPS();

	LoadData();

	return true;
}

/**
@brief  終了処理
*/
void Game::Termination()
{
	UnloadData();
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
		fps->Update();
		UpdateGame();
		physicsWorld->HitCheck();
		GenerateOutput();
	}
}

/**
@brief  ゲームに必要なデータのロード
*/
void Game::LoadData()
{
	  // Setup lights
	renderer->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = renderer->GetDirectionalLight();
	dir.direction = Vector3(0.0f, -0.707f, -0.707f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// Camera actor
	GameObject* mCameraActor = new PlayerObject(this);

	GAME_OBJECT_MANAGER->CreateInstance();

	for (int i = 0; i < 50; i++)
	{
		GameObject* a = new GameObject(this);
		a->SetScale(1000.0f);
		a->SetPosition(Vector3(i*2000.0f, 0.0f, 0.0f));
		MeshComponent* mc = new MeshComponent(a);
		mc->SetMesh(renderer->GetMesh("Assets/Wall.gpmesh"));
	}

}

/**
@brief   ロードしたデータの解放
*/
void Game::UnloadData()
{
	GAME_OBJECT_MANAGER->DeleteInstance();
	if (renderer)
	{
		renderer->UnloadData();
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
	renderer->Draw();
}

/**
@brief  ゲームのアップデート処理
*/
void Game::UpdateGame()
{
	float deltaTime = fps->GetDeltaTime();
	
	GAME_OBJECT_MANAGER->UpdateGameObject(deltaTime);
}