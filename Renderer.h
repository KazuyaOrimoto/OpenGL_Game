#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"

struct DirectionalLight
{
    // Direction of light
    Vector3 direction;
    // Diffuse color
    Vector3 diffuseColor;
    // Specular color
    Vector3 specColor;
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

    void SetViewMatrix(const Matrix4& argView) { view = argView; }

    void SetAmbientLight(const Vector3& argAmbient) { ambientLight = argAmbient; }
    DirectionalLight& GetDirectionalLight() { return dirLight; }

    float GetScreenWidth() const { return screenWidth; }
    float GetScreenHeight() const { return screenHeight; }
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
    Shader* spriteShader;
    // Sprite vertex array
    VertexArray* spriteVerts;

    // Mesh shader
    Shader* meshShader;

    // View/projection for 3D shaders
    Matrix4 view;
    Matrix4 projection;
    // Width/height of screen
    float screenWidth;
    float screenHeight;

    // Lighting data
    Vector3 ambientLight;
    DirectionalLight dirLight;

    // Window
    SDL_Window* window;
    // OpenGL context
    SDL_GLContext context;
};