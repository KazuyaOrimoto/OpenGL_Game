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

Game::Game()
    : fps(nullptr)
    , renderer(nullptr)
    , isRunning(true)
	, updatingGameObject(false)
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
@brief  �Q�[���I�u�W�F�N�g�̒ǉ�
@param	�ǉ�����GameObject�N���X�̃|�C���^
*/
void Game::AddGameObject(GameObject* argObj)
{
	if (updatingGameObject)
	{
		pendingGameObjects.emplace_back(argObj);
	}
	else
	{
		gameObjects.emplace_back(argObj);
	}
}

/**
@brief  �Q�[���I�u�W�F�N�g�̍폜
@param	�폜����GameObject�N���X�̃|�C���^
*/
void Game::RemoveGameObject(GameObject * argObj)
{
	auto iter = std::find(pendingGameObjects.begin(),pendingGameObjects.end(),argObj);
	if (iter != pendingGameObjects.end())
	{
		std::iter_swap(iter,pendingGameObjects.end() - 1);
		pendingGameObjects.pop_back();
	}

	iter = std::find(gameObjects.begin(),gameObjects.end(),argObj);
	if (iter != gameObjects.end())
	{
		std::iter_swap(iter,gameObjects.end()-1);
		gameObjects.pop_back();
	}
}

/**
@brief  �Q�[���ɕK�v�ȃf�[�^�̃��[�h
*/
void Game::LoadData()
{
    GameObject* a = new GameObject(this);
    a->SetPosition(Vector3(200.0f, 75.0f, 0.0f));
    a->SetScale(100.0f);
    Quaternion q(Vector3::UnitY, -Math::PiOver2);
    q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::Pi + Math::Pi / 4.0f));
    a->SetRotation(q);
    MeshComponent* mc = new MeshComponent(a);
    mc->SetMesh(renderer->GetMesh("Assets/Cube.gpmesh"));

    a = new SphereObject(this);
    //a->SetPosition(Vector3(200.0f, -75.0f, 0.0f));
    //a->SetScale(3.0f);
    //mc = new MeshComponent(a);
    //mc->SetMesh(renderer->GetMesh("Assets/Sphere.gpmesh"));

    // Setup floor
    const float start = -1250.0f;
    const float size = 250.0f;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            a = new PlaneObject(this);
            a->SetPosition(Vector3(start + i * size, start + j * size, -100.0f));
        }
    }

    // Left/right walls
    q = Quaternion(Vector3::UnitX, Math::PiOver2);
    for (int i = 0; i < 10; i++)
    {
        a = new PlaneObject(this);
        a->SetPosition(Vector3(start + i * size, start - size, 0.0f));
        a->SetRotation(q);

        a = new PlaneObject(this);
        a->SetPosition(Vector3(start + i * size, -start + size, 0.0f));
        a->SetRotation(q);
    }

    q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::PiOver2));
    // Forward/back walls
    for (int i = 0; i < 10; i++)
    {
        a = new PlaneObject(this);
        a->SetPosition(Vector3(start - size, start + i * size, 0.0f));
        a->SetRotation(q);

        a = new PlaneObject(this);
        a->SetPosition(Vector3(-start + size, start + i * size, 0.0f));
        a->SetRotation(q);
    }

    // Setup lights
    renderer->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
    DirectionalLight& dir = renderer->GetDirectionalLight();
    dir.direction = Vector3(0.0f, -0.707f, -0.707f);
    dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
    dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

    // Camera actor
    GameObject* mCameraActor = new FollowCameraObject(this);

    // UI elements
    a = new GameObject(this);
    a->SetPosition(Vector3(-350.0f, -350.0f, 0.0f));
    SpriteComponent* sc = new SpriteComponent(a);
    sc->SetTexture(renderer->GetTexture("Assets/HealthBar.png"));

    a = new GameObject(this);
    a->SetPosition(Vector3(375.0f, -275.0f, 0.0f));
    a->SetScale(0.75f);
    sc = new SpriteComponent(a);
    sc->SetTexture(renderer->GetTexture("Assets/Radar.png"));

}

/**
@brief   ���[�h�����f�[�^�̉��
*/
void Game::UnloadData()
{
	while (!gameObjects.empty())
	{
		delete gameObjects.back();
	}
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

	updatingGameObject = true;
	for (auto gameObject : gameObjects)
	{
		gameObject->ProcessInput(state);
	}
	updatingGameObject = false;

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
	updatingGameObject = true;
	float deltaTime = fps->GetDeltaTime();
	for (auto gameObject : gameObjects)
	{
		gameObject->Update(deltaTime);
	}
	updatingGameObject = false;

	for (auto pending : pendingGameObjects)
	{
		pending->ComputeWorldTransform();
		gameObjects.emplace_back(pending);
	}
	pendingGameObjects.clear();
}