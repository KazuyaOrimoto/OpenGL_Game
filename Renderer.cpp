#include "Renderer.h"
#include "Texture.h"
#include "Mesh.h"
#include <algorithm>
#include "Shader.h"
#include "VertexArray.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include <glew.h>

Renderer* Renderer::renderer = nullptr;

Renderer::Renderer()
    : spriteShader(nullptr)
	, spriteVerts(nullptr)
    , meshShader(nullptr)
	, view(Matrix4::Identity)
	, projection(Matrix4::Identity)
	, screenWidth(0)
	, screenHeight(0)
	, ambientLight(Vector3::Zero)
{
}

Renderer::~Renderer()
{
}

/**
@brief  インスタンスを作成する
*/
void Renderer::CreateInstance()
{
	if (renderer == nullptr)
	{
		renderer = new Renderer();
	}
}


/**
@brief  インスタンスを削除する
*/
void Renderer::DeleteInstance()
{
	if (renderer != nullptr)
	{
		delete renderer;
		renderer = nullptr;
	}
}

/**
@brief  初期化処理
@return true : 成功 , false : 失敗
*/
bool Renderer::Initialize(float argScreenWidth, float argScreenHeight)
{
    screenWidth = argScreenWidth;
    screenHeight = argScreenHeight;

    // OpenGLの各属性を設定する
    // コアOpenGLプロファイルを使う
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // OpenGLの使用バージョンを3.3に指定
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // RGBA各チャンネル8ビットのカラーバッファを使う
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    // ダブルバッファを有効にする
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // ハードウェアアクセラレーションを使う
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	//ウィンドウの作成
    window = SDL_CreateWindow("Game Programming in C++ (Chapter 6)", 100, 100,
        static_cast<int>(screenWidth), static_cast<int>(screenHeight), SDL_WINDOW_OPENGL);
    if (!window)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    // OpenGLのコンテキストを作成
    context = SDL_GL_CreateContext(window);

    // GLEWの初期化
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        SDL_Log("Failed to initialize GLEW.");
        return false;
    }

    // 一部のプラットフォームで出る無害なエラーコードをクリアする
    glGetError();

    // シェーダーのロード
    if (!LoadShaders())
    {
        SDL_Log("Failed to load shaders.");
        return false;
    }

    //スプライト用の頂点配列を作成
    CreateSpriteVerts();

    return true;
}

/**
@brief  終了処理
*/
void Renderer::Shutdown()
{
    delete spriteVerts;
    spriteShader->Unload();
    delete spriteShader;
    meshShader->Unload();
    delete meshShader;
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
}

/**
@brief  ロードしたデータの解放
*/
void Renderer::UnloadData()
{
    // すべてのテクスチャのデータを解放
    for (auto i : textures)
    {
        i.second->Unload();
        delete i.second;
    }
	textures.clear();

    // すべてのメッシュのデータを解放
    for (auto i : meshes)
    {
        i.second->Unload();
        delete i.second;
    }
	meshes.clear();
}

/**
@brief  描画処理
*/
void Renderer::Draw()
{
    // クリアカラーを灰色に設定
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // カラーバッファとデプスバッファをクリア
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // メッシュコンポーネントの描画
    // デプスバッファ法を有効にする
    glEnable(GL_DEPTH_TEST);
	//アルファブレンディングを無効にする
    glDisable(GL_BLEND);
    // 基本的なメッシュシェーダーをアクティブにする
    meshShader->SetActive();
    // ビュー射影行列を更新する
    meshShader->SetMatrixUniform("uViewProj", view * projection);
    // シェーダーに渡すライティング情報を更新する
    SetLightUniforms(meshShader);
	// すべてのメッシュの描画
    for (auto mc : meshComponents)
    {
		if (mc->GetVisible())
		{
			mc->Draw(meshShader);
		}
    }

    // スプライトコンポーネントの描画
    // デプスバッファ法を無効にする
    glDisable(GL_DEPTH_TEST);
    // アルファブレンディングを有効にする
    glEnable(GL_BLEND);
	// RGB成分とα成分のブレンディング方法を別々に設定
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	// RGB成分とアルファ成分に別々の混合係数を設定
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    // スプライトシェーダーをアクティブにする/スプライト頂点配列を有効にする
    spriteShader->SetActive();
    spriteVerts->SetActive();
	// すべてのスプライトの描画
    for (auto sprite : sprites)
    {
        sprite->Draw(spriteShader);
    }

    // バッファを交換
    SDL_GL_SwapWindow(window);
}

/**
@brief  スプライトの削除
@param	削除するSpriteComponentクラスのポインタ
*/
void Renderer::AddSprite(SpriteComponent* argSpriteComponent)
{
    // 今あるスプライトから挿入する場所の検索
    // (DrawOrderが小さい順番に描画するため)
	int myDrawOrder = argSpriteComponent->GetDrawOrder();
    auto iter = sprites.begin();
    for (;
        iter != sprites.end();
        ++iter)
    {
        if (myDrawOrder < (*iter)->GetDrawOrder())
        {
            break;
        }
    }

    // 検索した場所のiterの場所に挿入
	sprites.insert(iter, argSpriteComponent);
}

/**
@brief  スプライトの削除
@param	削除するSpriteComponentクラスのポインタ
*/
void Renderer::RemoveSprite(SpriteComponent* argSpriteComponent)
{
    auto iter = std::find(sprites.begin(), sprites.end(), argSpriteComponent);
	sprites.erase(iter);
}

/**
@brief  メッシュコンポーネントの追加
@param	追加するMeshComponentクラスのポインタ
*/
void Renderer::AddMeshComponent(MeshComponent* argMeshComponent)
{
	meshComponents.emplace_back(argMeshComponent);
}

/**
@brief  メッシュコンポーネントの削除
@param	削除するMeshComponentクラスのポインタ
*/
void Renderer::RemoveMeshComponent(MeshComponent* argMeshComponent)
{
    auto iter = std::find(meshComponents.begin(), meshComponents.end(), argMeshComponent);
    meshComponents.erase(iter);
}

/**
@brief  テクスチャの取得
@param	取得したいテクスチャのファイル名
@return Textureクラスのポインタ
*/
Texture* Renderer::GetTexture(const std::string& argFileName)
{
	Texture* texture = nullptr;
	//すでに作成されてないか調べる
	auto itr = textures.find(argFileName);
	if (itr != textures.end())
	{
		texture = itr->second;
	}
	//作成済みでない場合、新しくテクスチャを作成
	else
	{
		texture = new Texture();
		if (texture->Load(argFileName))
		{
			textures.emplace(argFileName, texture);
		}
		else
		{
			delete texture;
			texture = nullptr;
		}
	}

	return texture;
}

/**
@brief  メッシュの取得
@param	取得したいメッシュのファイル名
@return Meshクラスのポインタ
*/
Mesh* Renderer::GetMesh(const std::string &argFfileName)
{
    Mesh* m = nullptr;
	//すでに作成されてないか調べる
    auto iter = meshes.find(argFfileName);
    if (iter != meshes.end())
    {
        m = iter->second;
    }
	//作成済みでない場合、新しくメッシュを作成
    else
    {
        m = new Mesh();
        if (m->Load(argFfileName, this))
        {
			meshes.emplace(argFfileName, m);
        }
        else
        {
            delete m;
            m = nullptr;
        }
    }
    return m;
}

/**
@brief  シェーダーの読み込み
@return true : 成功 , false : 失敗
*/
bool Renderer::LoadShaders()
{
    // スプライトシェーダーの作成
    spriteShader = new Shader();
    if (!spriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
    {
        return false;
    }

    spriteShader->SetActive();
    // ビュー行列の設定
    Matrix4 viewProj = Matrix4::CreateSimpleViewProj(screenWidth, screenHeight);
    spriteShader->SetMatrixUniform("uViewProj", viewProj);

    // 標準のメッシュシェーダーの作成
    meshShader = new Shader();
    if (!meshShader->Load("Shaders/Phong.vert", "Shaders/Phong.frag"))
    {
        return false;
    }

    meshShader->SetActive();
    // ビュー行列の設定
    view = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
    projection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f),
        screenWidth, screenHeight, 25.0f, 10000.0f);
    meshShader->SetMatrixUniform("uViewProj", view * projection);
    return true;
}

/**
@brief  Sprite用の頂点バッファとインデックスバッファの作成
*/
void Renderer::CreateSpriteVerts()
{
    float vertices[] = {
        -0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // 左上
        0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // 右上
        0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // 右下
        -0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // 左下
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    spriteVerts = new VertexArray(vertices, 4, indices, 6);
}


/**
@brief  光源情報をシェーダーの変数にセットする
@param  セットするShaderクラスのポインタ
*/
void Renderer::SetLightUniforms(Shader* shader)
{
	// ビュー行列を転置行列にする
    Matrix4 invView = view;
    invView.Invert();
    shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
    // 環境光の設定
    shader->SetVectorUniform("uAmbientLight", ambientLight);
    // 平行光源の設定
    shader->SetVectorUniform("uDirLight.mDirection",
        dirLight.direction);
    shader->SetVectorUniform("uDirLight.mDiffuseColor",
        dirLight.diffuseColor);
    shader->SetVectorUniform("uDirLight.mSpecColor",
        dirLight.specColor);
}
