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

Game::Game()
    : fps(nullptr)
    , window(nullptr)
    , context()
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

    //�R�AOpenGL�v���t�@�C�����g��
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    //OpenGL�̎g�p�o�[�W������3.3�Ɏw��
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    //RGBA�e�`�����l��8�r�b�g�̃J���[�o�b�t�@���g��
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    //�_�u���o�b�t�@��L���ɂ���
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    //�n�[�h�E�F�A�A�N�Z�����[�V�������g��
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	window = SDL_CreateWindow("OpenGL Game", 100, 100, 1024, 768, SDL_WINDOW_OPENGL);
	if (!window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

    context = SDL_GL_CreateContext(window);

    //GLEW�̏�����
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        SDL_Log("Failed to initialize GLEW.");
        return false;
    }

    //�ꕔ�̃v���b�g�t�H�[���ŏo�閳�Q�ȃG���[�R�[�h���N���A����
    glGetError();

	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}

	CreateSpriteVerts();

	LoadData();

	fps = new FPS();


	return true;
}

/**
@brief  �I������
*/
void Game::Termination()
{
	UnloadData();
	delete spriteVerts;
	spriteShader->Unload();
	delete spriteShader;
    SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
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

void Game::AddSprite(SpriteComponent * argSprite)
{
	int DrawOder = argSprite->readOnlyDrawOrder;
	auto itr = sprites.begin();
	for ( ;itr != sprites.end();++itr)
	{
		if (DrawOder < (*itr)->readOnlyDrawOrder)
		{
			break;
		}
	}

	sprites.insert(itr, argSprite);
}

void Game::RemoveSprite(SpriteComponent * argSprite)
{
	auto itr = std::find(sprites.begin(),sprites.end(),argSprite);
	sprites.erase(itr);
}

Texture * Game::GetTexture(const std::string & argFileName)
{
	Texture* texture = nullptr;
	auto itr = textures.find(argFileName);
	if (itr != textures.end())
	{
		texture = itr->second;
	}
	else
	{
		texture = new Texture();
		if (texture->Load(argFileName))
		{
			textures.emplace(argFileName,texture);
		}
		else
		{
			delete texture;
			texture = nullptr;
		}
	}

	return texture;
}

void Game::LoadData()
{
	ship = new Ship(this);

}

void Game::UnloadData()
{
	while (!gameObjects.empty())
	{
		delete gameObjects.back();
	}
	for (auto itr : textures)
	{
		itr.second->Unload();
		delete itr.second;
	}
	textures.clear();
}

/**
@brief  ���͊֘A�̏���
*/
void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE])
    {
        isRunning = false;
    }
}

/**
@brief  �`��֘A�̏���
*/
void Game::GenerateOutput()
{
    //�N���A�J���[���D�F�ɐݒ�
    glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
    //�J���[�o�b�t�@���N���A
    glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //�V�[����`��
	spriteShader->SetActive();
	spriteVerts->SetActive();

	for (auto sprite : sprites)
	{
		sprite->Draw(spriteShader);
	}

    //�o�b�t�@������
    SDL_GL_SwapWindow(window);
}

void Game::UpdateGame()
{
	updatingGameObject = true;
	for (auto gameObject : gameObjects)
	{
		gameObject->Update(0.05f);
	}
	updatingGameObject = false;

	for (auto pending : pendingGameObjects)
	{
		pending->ComputeWorldTransform();
		gameObjects.emplace_back(pending);
	}
	pendingGameObjects.clear();


}

bool Game::LoadShaders()
{
	spriteShader = new Shader();
	if (!spriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}
	spriteShader->SetActive();

	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1024.f,768.f);
	spriteShader->SetMatrixUniform("uViewProj", viewProj);
	return true;

}

void Game::CreateSpriteVerts()
{
	float vertices[] = {
	-0.5f,  0.5f, 0.f, 0.f, 0.f, // top left
	 0.5f,  0.5f, 0.f, 1.f, 0.f, // top right
	 0.5f, -0.5f, 0.f, 1.f, 1.f, // bottom right
	-0.5f, -0.5f, 0.f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	spriteVerts = new VertexArray(vertices,4,indices,6);
}
