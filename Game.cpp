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

Game::Game()
	: fps(nullptr)
	, renderer(nullptr)
    , isRunning(true)
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

    GameObjectManager::CreateInstance();
    GameObjectCreater::CreateInstance();

	LoadData();

	return true;
}

/**
@brief  �I������
*/
void Game::Termination()
{
    GameObjectManager::DeleteInstance();
    GameObjectCreater::DeleteInstance();
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

    GAME_OBJECT_CREATER->PlayerAndWallCreate(*this);
}

/**
@brief   ���[�h�����f�[�^�̉��
*/
void Game::UnloadData()
{
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