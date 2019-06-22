#pragma once
#include <vector>
#include "Math.h"

class Game;
class Vector3;
class Matrix4;
class Component;
struct InputState;

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

	void ProcessInput(const InputState& keyState);
	virtual void GameObjectInput(const InputState& keyState);

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

	/**
	@brief　オブジェクトのポジションを取得する
	@return	position
	*/
    const Vector3& GetPosition() const { return position; }

	/**
	@brief　オブジェクトのポジションを設定する
	@param	position
	*/
    void SetPosition(const Vector3& argPos) { position = argPos; recomputeWorldTransform = true; }

	/**
	@brief　オブジェクトのスケールを取得する
	@return	scale
	*/
    float GetScale() const { return scale; }

	/**
	@brief　オブジェクトのスケールを設定する
	@param	scale
	*/
    void SetScale(float argScale) { scale = argScale;  recomputeWorldTransform = true; }

	/**
	@brief　オブジェクトのクォータニオンを取得する
	@return	rotation（Quaternion型）
	*/
    const Quaternion& GetRotation() const { return rotation; }

	/**
	@brief　オブジェクトのクォータニオンを設定する
	@param	rotation（Quaternion型）
	*/
    void SetRotation(const Quaternion& argQotation) { rotation = argQotation;  recomputeWorldTransform = true; }

	/**
	@brief　オブジェクトの状態を取得する
	@return	state
	*/
	State GetState() const { return state; }

	/**
	@brief　オブジェクトの状態を設定する
	@param	state
	*/
	void SetState(State argState) { state = argState; }

	/**
	@brief　オブジェクトのワールド行列を取得する
	@return	worldTransform
	*/
	const Matrix4& GetWorldTransform() const { return worldTransform; }

	/**
	@brief　Gameクラスのインスタンスを取得する
	@return	Gameクラスのポインタ
	*/
    Game* GetGame() { return game; }

	/**
	@brief　オブジェクトの前方を表すベクトルを取得する
	@param	forward(Vector3型)
	*/
    Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, rotation); }

protected:
	//ゲームオブジェクトの状態
	State state;

	//Transform
	Vector3 position;
	Quaternion rotation;	
	float scale;
	Matrix4 worldTransform;
	//ワールド変換の処理を行う必要性があるか
	bool recomputeWorldTransform;

	//アタッチされているコンポーネント
	std::vector<class Component*>components;
	//ゲームクラスのインスタンス
	Game* game;

};

