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

    //コアOpenGLプロファイルを使う
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    //OpenGLの使用バージョンを3.3に指定
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    //RGBA各チャンネル8ビットのカラーバッファを使う
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    //ダブルバッファを有効にする
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    //ハードウェアアクセラレーションを使う
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	window = SDL_CreateWindow("OpenGL Game", 100, 100, 1024, 768, SDL_WINDOW_OPENGL);
	if (!window)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

    context = SDL_GL_CreateContext(window);

    //GLEWの初期化
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        SDL_Log("Failed to initialize GLEW.");
        return false;
    }

    //一部のプラットフォームで出る無害なエラーコードをクリアする
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
@brief  終了処理
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
@brief  ゲームループ
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
@brief  ゲームオブジェクトの追加
@param	追加するGameObjectクラスのポインタ
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
@brief  ゲームオブジェクトの削除
@param	削除するGameObjectクラスのポインタ
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
@brief  入力関連の処理
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
@brief  描画関連の処理
*/
void Game::GenerateOutput()
{
    //クリアカラーを灰色に設定
    glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
    //カラーバッファをクリア
    glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //シーンを描画
	spriteShader->SetActive();
	spriteVerts->SetActive();

	for (auto sprite : sprites)
	{
		sprite->Draw(spriteShader);
	}

    //バッファを交換
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
