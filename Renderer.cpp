#include "Renderer.h"
#include "Texture.h"
#include "Mesh.h"
#include <algorithm>
#include "Shader.h"
#include "VertexArray.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include <glew.h>

Renderer::Renderer(Game* argGame)
    : game(argGame)
    , spriteShader(nullptr)
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
@brief  初期化処理
@return true : 成功 , false : 失敗
*/
bool Renderer::Initialize(float argScreenWidth, float argScreenHeight)
{
    screenWidth = argScreenWidth;
    screenHeight = argScreenHeight;

    // Set OpenGL attributes
    // Use the core OpenGL profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // Specify version 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // Request a color buffer with 8-bits per RGBA channel
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    // Enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // Force OpenGL to use hardware acceleration
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    window = SDL_CreateWindow("Game Programming in C++ (Chapter 6)", 100, 100,
        static_cast<int>(screenWidth), static_cast<int>(screenHeight), SDL_WINDOW_OPENGL);
    if (!window)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    // Create an OpenGL context
    context = SDL_GL_CreateContext(window);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        SDL_Log("Failed to initialize GLEW.");
        return false;
    }

    // On some platforms, GLEW will emit a benign error code,
    // so clear it
    glGetError();

    // Make sure we can create/compile shaders
    if (!LoadShaders())
    {
        SDL_Log("Failed to load shaders.");
        return false;
    }

    // Create quad for drawing sprites
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
    // Destroy textures
    for (auto i : textures)
    {
        i.second->Unload();
        delete i.second;
    }
	textures.clear();

    // Destroy meshes
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
    // Set the clear color to light grey
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw mesh components
    // Enable depth buffering/disable alpha blend
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    // Set the mesh shader active
    meshShader->SetActive();
    // Update view-projection matrix
    meshShader->SetMatrixUniform("uViewProj", view * projection);
    // Update lighting uniforms
    SetLightUniforms(meshShader);
    for (auto mc : meshComponents)
    {
        mc->Draw(meshShader);
    }

    // Draw all sprite components
    // Disable depth buffering
    glDisable(GL_DEPTH_TEST);
    // Enable alpha blending on the color buffer
    glEnable(GL_BLEND);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    // Set shader/vao as active
    spriteShader->SetActive();
    spriteVerts->SetActive();
    for (auto sprite : sprites)
    {
        sprite->Draw(spriteShader);
    }

    // Swap the buffers
    SDL_GL_SwapWindow(window);
}

/**
@brief  スプライトの削除
@param	削除するSpriteComponentクラスのポインタ
*/
void Renderer::AddSprite(SpriteComponent* argSpriteComponent)
{
    // Find the insertion point in the sorted vector
    // (The first element with a higher draw order than me)
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

    // Inserts element before position of iterator
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
    auto iter = meshes.find(argFfileName);
    if (iter != meshes.end())
    {
        m = iter->second;
    }
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
    // Create sprite shader
    spriteShader = new Shader();
    if (!spriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
    {
        return false;
    }

    spriteShader->SetActive();
    // Set the view-projection matrix
    Matrix4 viewProj = Matrix4::CreateSimpleViewProj(screenWidth, screenHeight);
    spriteShader->SetMatrixUniform("uViewProj", viewProj);

    // Create basic mesh shader
    meshShader = new Shader();
    if (!meshShader->Load("Shaders/Phong.vert", "Shaders/Phong.frag"))
    {
        return false;
    }

    meshShader->SetActive();
    // Set the view-projection matrix
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
        -0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // top left
        0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // top right
        0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // bottom right
        -0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // bottom left
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
    // Camera position is from inverted view
    Matrix4 invView = view;
    invView.Invert();
    shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
    // Ambient light
    shader->SetVectorUniform("uAmbientLight", ambientLight);
    // Directional light
    shader->SetVectorUniform("uDirLight.mDirection",
        dirLight.direction);
    shader->SetVectorUniform("uDirLight.mDiffuseColor",
        dirLight.diffuseColor);
    shader->SetVectorUniform("uDirLight.mSpecColor",
        dirLight.specColor);
}
