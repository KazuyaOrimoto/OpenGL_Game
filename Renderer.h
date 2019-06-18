#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"

struct DirectionalLight
{
    // Direction of light
    Vector3 mDirection;
    // Diffuse color
    Vector3 mDiffuseColor;
    // Specular color
    Vector3 mSpecColor;
};

class SpriteComponent;
class Texture;
class Mesh;
class Game;
class MeshComponent;
class Shader;
class VertexArray;

class Renderer
{
public:
    Renderer(Game* argGame);
    ~Renderer();

    bool Initialize(float argScreenWidth, float argScreenHeight);
    void Shutdown();
    void UnloadData();

    void Draw();

	/**
	@brief  スプライトの追加
	@param	追加するSpriteComponentクラスのポインタ
	*/
	void AddSprite(SpriteComponent* argSpriteComponent);

	/**
	@brief  スプライトの削除
	@param	削除するSpriteComponentクラスのポインタ
	*/
	void RemoveSprite(SpriteComponent* argSpriteComponent);

	/**
	@brief  テクスチャの取得
	@param	取得したいテクスチャのファイル名
	@return テクスチャのポインタ
	*/
	Texture* GetTexture(const std::string& argFileName);


    void AddMeshComp(MeshComponent* argMeshComponent);
    void RemoveMeshComp(MeshComponent* argMeshComponent);

    Mesh* GetMesh(const std::string& argFileName);

    void SetViewMatrix(const Matrix4& argView) { mView = argView; }

    void SetAmbientLight(const Vector3& argAmbient) { mAmbientLight = argAmbient; }
    DirectionalLight& GetDirectionalLight() { return mDirLight; }

    float GetScreenWidth() const { return mScreenWidth; }
    float GetScreenHeight() const { return mScreenHeight; }
private:
	/**
	@brief  シェーダーの読み込み
	*/
    bool LoadShaders();
	/**
	@brief  Sprite用の頂点バッファとインデックスバッファの作成
	*/
    void CreateSpriteVerts();
    void SetLightUniforms(Shader* argShader);

    // Map of meshes loaded
    std::unordered_map<std::string, Mesh*> meshes;

    // All mesh components drawn
    std::vector<MeshComponent*> meshComponents;

	//スプライトコンポーネントのポインタの可変長コンテナ
	std::vector<SpriteComponent*> sprites;
	//ファイル名でテクスチャを取得するための可変長コンテナ
	std::unordered_map<std::string, Texture*>textures;

    // Game
    Game* game;

    // Sprite shader
    Shader* mSpriteShader;
    // Sprite vertex array
    VertexArray* mSpriteVerts;

    // Mesh shader
    Shader* mMeshShader;

    // View/projection for 3D shaders
    Matrix4 mView;
    Matrix4 mProjection;
    // Width/height of screen
    float mScreenWidth;
    float mScreenHeight;

    // Lighting data
    Vector3 mAmbientLight;
    DirectionalLight mDirLight;

    // Window
    SDL_Window* mWindow;
    // OpenGL context
    SDL_GLContext mContext;
};