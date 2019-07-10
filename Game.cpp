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
@brief  ����������
@return true : ���� , false : ���s
*/
bool Game::Initialize()
{
	//SDL�̏�����
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	//�����_���[�̏�����
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

	//FPS�Ǘ��N���X�̏�����
	fps = new FPS();

	LoadData();

	return true;
}

/**
@brief  �I������
*/
void Game::Termination()
{
	UnloadData();
	SDL_Quit();
}

/**
@brief  �Q�[�����[�v
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
@brief  �Q�[���ɕK�v�ȃf�[�^�̃��[�h
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
@brief   ���[�h�����f�[�^�̉��
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
@brief  ���͊֘A�̏���
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
@brief  �`��֘A�̏���
*/
void Game::GenerateOutput()
{
	renderer->Draw();
}

/**
@brief  �Q�[���̃A�b�v�f�[�g����
*/
void Game::UpdateGame()
{
	float deltaTime = fps->GetDeltaTime();
	
	GAME_OBJECT_MANAGER->UpdateGameObject(deltaTime);
}