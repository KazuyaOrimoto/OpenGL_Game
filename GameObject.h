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

	/**
	@brief	Transformのワールド変換
	*/
	void ComputeWorldTransform();

	void SetRotation(float argRotation) { rotation = argRotation;  recomputeWorldTransform = true; }
	const Matrix4& GetWorldTransform() const { return worldTransform; }


	cpp_module::ReadOnlyProperty<Vector2> readOnlyPosition;
    cpp_module::ReadOnlyProperty<Game*> readOnlyGame;
	cpp_module::ReadOnlyProperty<Matrix4> readOnlyWorldTransform;

protected:
	//ゲームオブジェクトの状態
	State state;

	//Transform
	Vector2 position;
	float scale;
	float rotation;	

	Matrix4 worldTransform;
	//ワールド変換の処理を行う必要性があるか
	bool recomputeWorldTransform;

	//アタッチされているコンポーネント
	std::vector<class Component*>components;
	//ゲームクラスのインスタンス
	Game* game;

};

