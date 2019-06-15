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
class Renderer;

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
	///**
	//@brief  スプライトの追加
	//@param	追加するSpriteComponentクラスのポインタ
	//*/
 //   void AddSprite(SpriteComponent* argSprite);
	///**
	//@brief  スプライトの削除
	//@param	削除するSpriteComponentクラスのポインタ
	//*/
	//void RemoveSprite(SpriteComponent* argSprite);

	///**
	//@brief  テクスチャの取得
	//@param	取得したいテクスチャのファイル名
	//@return テクスチャのポインタ
	//*/
	//Texture* GetTexture(const std::string& argFileName);

    class Renderer* GetRenderer() { return renderer; }


private:
	/**
	@brief  入力関連の処理
	*/
    void ProcessInput();
	/**
	@brief  描画関連の処理
	*/
    void GenerateOutput();

	/**
	@brief  ゲームのアップデート処理
	*/
	void UpdateGame();

	/**
	@brief  シェーダーの読み込み
	*/
	bool LoadShaders();

	/**
	@brief  Sprite用の頂点バッファとインデックスバッファの作成
	*/
	void CreateSpriteVerts();

	/**
	@brief  ゲームに必要なデータのロード
	*/
	void LoadData();

	/**
	@brief  ゲームで使ったデータの解放
	*/
	void UnloadData();

	FPS*            fps;

	//ゲームオブジェクトのポインタの可変長コンテナ
	std::vector<GameObject*> gameObjects;
	//Update中に追加されたゲームオブジェクトのポインタを一時的に保存する可変長コンテナ
	std::vector<GameObject*> pendingGameObjects;
	////スプライトコンポーネントのポインタの可変長コンテナ
	//std::vector<SpriteComponent*> sprites;
	////ファイル名でテクスチャを取得するための可変長コンテナ
	//std::unordered_map<std::string, Texture*>textures;

    Renderer* renderer;

	//ゲームを続けるかどうか
    bool isRunning;
	//Update中かどうか
	bool updatingGameObject;

};

