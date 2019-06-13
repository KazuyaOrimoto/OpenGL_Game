#pragma once
#include "SDL.h"
#include <unordered_map>
#include <vector>
#include <string>

class FPS;
class GameObject;
class Texture;
class Ship;
class Shader;
class SpriteComponent;
class VertexArray;
struct SDL_Window;
struct SDL_Renderer;

class Game
{
public:
	Game();
	~Game();
	/**
	@brief  初期化処理
	@return true : 成功 , false : 失敗
	*/
	bool Initialize();
	/**
	@brief  終了処理
	*/
	void Termination();
	/**
	@brief  ゲームループ
	*/
	void GameLoop();
	
	/**
	@brief  ゲームオブジェクトの追加
	@param	追加するGameObjectクラスのポインタ
	*/
	void AddGameObject(GameObject* argObj);
	/**
	@brief  ゲームオブジェクトの削除
	@param	削除するGameObjectクラスのポインタ
	*/
	void RemoveGameObject(GameObject* argObj);
	/**
	@brief  スプライトの追加
	@param	追加するSpriteComponentクラスのポインタ
	*/
    void AddSprite(SpriteComponent* argSprite);
	/**
	@brief  スプライトの削除
	@param	削除するSpriteComponentクラスのポインタ
	*/
	void RemoveSprite(SpriteComponent* argSprite);

	Texture* GetTexture(const std::string& argFileName);


private:
	/**
	@brief  入力関連の処理
	*/
    void ProcessInput();
	/**
	@brief  描画関連の処理
	*/
    void GenerateOutput();

	void UpdateGame();

	bool LoadShaders();
	void CreateSpriteVerts();

	void LoadData();
	void UnloadData();

	FPS*            fps;
	SDL_Window*     window;
    SDL_GLContext   context;

	//ゲームオブジェクトのポインタの可変長コンテナ
	std::vector<GameObject*> gameObjects;
	//Update中に追加されたゲームオブジェクトのポインタを一時的に保存する可変長コンテナ
	std::vector<GameObject*> pendingGameObjects;
	//スプライトコンポーネントのポインタの可変長コンテナ
	std::vector<SpriteComponent*> sprites;

	std::unordered_map<std::string, Texture*>textures;

	//ゲームを続けるかどうか
    bool isRunning;
	//Update中かどうか
	bool updatingGameObject;

	Shader* spriteShader;
	VertexArray* spriteVerts;

	Ship* ship;

};

