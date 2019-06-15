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

    renderer = new Renderer(this);
    if (!renderer->Initialize(1024.0f, 768.0f))
    {
        SDL_Log("Failed to initialize renderer");
        delete renderer;
        renderer = nullptr;
        return false;
    }
 

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

///**
//@brief  スプライトの追加
//@param	追加するSpriteComponentクラスのポインタ
//*/
//void Game::AddSprite(SpriteComponent * argSprite)
//{
//	int DrawOder = argSprite->readOnlyDrawOrder;
//	auto itr = sprites.begin();
//	for ( ;itr != sprites.end();++itr)
//	{
//		if (DrawOder < (*itr)->readOnlyDrawOrder)
//		{
//			break;
//		}
//	}
//
//	sprites.insert(itr, argSprite);
//}
//
///**
//@brief  スプライトの削除
//@param	削除するSpriteComponentクラスのポインタ
//*/
//void Game::RemoveSprite(SpriteComponent * argSprite)
//{
//	auto itr = std::find(sprites.begin(),sprites.end(),argSprite);
//	sprites.erase(itr);
//}

///**
//@brief  テクスチャの取得
//@param	取得したいテクスチャのファイル名
//@return テクスチャのポインタ
//*/
//Texture * Game::GetTexture(const std::string & argFileName)
//{
//	Texture* texture = nullptr;
//	auto itr = textures.find(argFileName);
//	if (itr != textures.end())
//	{
//		texture = itr->second;
//	}
//	else
//	{
//		texture = new Texture();
//		if (texture->Load(argFileName))
//		{
//			textures.emplace(argFileName,texture);
//		}
//		else
//		{
//			delete texture;
//			texture = nullptr;
//		}
//	}
//
//	return texture;
//}

/**
@brief  ゲームに必要なデータのロード
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

    renderer->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
    DirectionalLight& dir = renderer->GetDirectionalLight();
    dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
    dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
    dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);

    // Camera actor
    CameraObject* mCameraActor = new CameraObject(this);

}

/**
@brief  ゲームで使ったデータの解放
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
    renderer->Draw();

}

/**
@brief  ゲームのアップデート処理
*/
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
//
///**
//@brief  シェーダーの読み込み
//*/
//bool Game::LoadShaders()
//{
//	if (!spriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
//	{
//		return false;
//	}
//	spriteShader->SetActive();
//
//	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1024.f,768.f);
//	spriteShader->SetMatrixUniform("uViewProj", viewProj);
//	return true;
//
//}

///**
//@brief  Sprite用の頂点バッファとインデックスバッファの作成
//*/
//void Game::CreateSpriteVerts()
//{
//	float vertices[] = {
//	-0.5f,  0.5f, 0.f, 0.f, 0.f, // top left
//	 0.5f,  0.5f, 0.f, 1.f, 0.f, // top right
//	 0.5f, -0.5f, 0.f, 1.f, 1.f, // bottom right
//	-0.5f, -0.5f, 0.f, 0.f, 1.f  // bottom left
//	};
//
//	unsigned int indices[] = {
//		0, 1, 2,
//		2, 3, 0
//	};
//
//	spriteVerts = new VertexArray(vertices,4,indices,6);
//}
