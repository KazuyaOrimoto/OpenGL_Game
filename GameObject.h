#pragma once
#include <vector>
#include "Math.h"
#include "Property.h"

class Game;
class Vector2;
class Component;

class GameObject
{
public:
	/**
	@brief	ゲームオブジェクトの状態
	*/
	enum State
	{
		Active,
		Paused,
		Dead
	};

	/**
	@param	ゲームクラスのポインタ
	*/
	GameObject(Game* argGame);
	virtual ~GameObject();

	/**
	@brief	フレーム毎の処理
	@param	最後のフレームを完了するのに要した時間
	*/
	void Update(float argDaltaTime);

	/**
	@brief	アタッチされてるコンポーネントのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateComponents(float argDaltaTime);

	/**
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void UpdateGameObject(float argDaltaTime);

	/**
	@brief	コンポーネントを追加する
	@param	追加するコンポーネントのポインタ
	*/
	void AddComponent(Component* argComponent);

	/**
	@brief	コンポーネントを削除する
	@param	削除するコンポーネントのポインタ
	*/
	void RemoveComponent(Component* argComponent);

	cpp_module::ReadOnlyProperty<Vector2> readOnlyPosition;		//読み込み専用のポジション

private:

	State state;												//ゲームオブジェクトの状態

	Vector2 position;											//位置
	float scale;												//大きさ（比率）
	float rotation;												//回転

	std::vector<class Component*>components;					//アタッチされているコンポーネント
	Game* game;													//ゲームクラスのインスタンス

};

