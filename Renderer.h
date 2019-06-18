#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <SDL.h>
#include "Math.h"

//平行光源用の構造体
struct DirectionalLight
{
    // 光の方向
    Vector3 direction;
    // 拡散反射色
    Vector3 diffuseColor;
    // 鏡面反射色
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

	/**
	@brief  初期化処理
	@return true : 成功 , false : 失敗
	*/
    bool Initialize(float argScreenWidth, float argScreenHeight);
	/**
	@brief  終了処理
	*/
    void Shutdown();

	/**
	@brief  ロードしたデータの解放
	*/
    void UnloadData();

	/**
	@brief  描画処理
	*/
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
	@return Textureクラスのポインタ
	*/
	Texture* GetTexture(const std::string& argFileName);

	/**
	@brief  メッシュコンポーネントの追加
	@param	追加するMeshComponentクラスのポインタ
	*/
    void AddMeshComponent(MeshComponent* argMeshComponent);

	/**
	@brief  メッシュコンポーネントの削除
	@param	削除するMeshComponentクラスのポインタ
	*/
    void RemoveMeshComponent(MeshComponent* argMeshComponent);

	/**
	@brief  メッシュの取得
	@param	取得したいメッシュのファイル名
	@return Meshクラスのポインタ
	*/
    Mesh* GetMesh(const std::string& argFileName);

	// Getter / Setter

    void SetViewMatrix(const Matrix4& argView) { view = argView; }
    void SetAmbientLight(const Vector3& argAmbient) { ambientLight = argAmbient; }
    DirectionalLight& GetDirectionalLight() { return dirLight; }
    float GetScreenWidth() const { return screenWidth; }
    float GetScreenHeight() const { return screenHeight; }

private:
	/**
	@brief  シェーダーの読み込み
	@return true : 成功 , false : 失敗
	*/
    bool LoadShaders();
	/**
	@brief  Sprite用の頂点バッファとインデックスバッファの作成
	*/
    void CreateSpriteVerts();

	/**
	@brief  光源情報をシェーダーの変数にセットする
	@param  セットするShaderクラスのポインタ
	*/
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