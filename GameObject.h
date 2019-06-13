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

	void ComputeWorldTransform();


	cpp_module::ReadOnlyProperty<Vector2> readOnlyPosition;
    cpp_module::ReadOnlyProperty<Game*> readOnlyGame;
	cpp_module::ReadOnlyProperty<Matrix4> readOnlyWorldTransform;

private:
	//ゲームオブジェクトの状態
	State state;

	//Transform
	Matrix4 worldTransform;
	Vector2 position;
	float scale;
	float rotation;	
	bool recomputeWorldTransform;

	//アタッチされているコンポーネント
	std::vector<class Component*>components;
	//ゲームクラスのインスタンス
	Game* game;

};

