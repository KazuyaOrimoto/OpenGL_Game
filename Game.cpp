#include "Game.h"
#include "SDL.h"
#include <glew.h>
#include <algorithm>
#include "FPS.h"
#include "GameObject.h"

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


	fps = new FPS();


	return true;
}

/**
@brief  終了処理
*/
void Game::Termination()
{
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

    //シーンを描画

    //バッファを交換
    SDL_GL_SwapWindow(window);
}
