#pragma once
#include <vector>
#include "Math.h"

class Game;
class Vector3;
class Matrix4;
class Component;
struct InputState;

enum Tag
{
	Player,
	Obstacle,
	Wall
};

/**
@brief	ゲームオブジェクトの状態
*/
enum State
{
	Active,
	Paused,
	Dead
};

class GameObject
{
public:
	/**
	@param	ゲームクラスのポインタ
	*/
	GameObject(Game* _game);
	virtual ~GameObject();

	/**
	@brief	フレーム毎の処理
	@param	最後のフレームを完了するのに要した時間
	*/
	void Update(float _deltaTime);

	/**
	@brief	アタッチされてるコンポーネントのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateComponents(float _deltaTime);

	/**
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void UpdateGameObject(float _deltaTime);

	void ProcessInput(const InputState& _keyState);
	virtual void GameObjectInput(const InputState& _keyState);

	/**
	@brief	コンポーネントを追加する
	@param	追加するコンポーネントのポインタ
	*/
	void AddComponent(Component* _component);

	/**
	@brief	コンポーネントを削除する
	@param	削除するコンポーネントのポインタ
	*/
	void RemoveComponent(Component* _component);

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
    void SetPosition(const Vector3& _pos) { position = _pos; recomputeWorldTransform = true; }

	/**
	@brief　オブジェクトのスケールを取得する
	@return	scale
	*/
    float GetScale() const { return scale; }

	/**
	@brief　オブジェクトのスケールを設定する
	@param	scale
	*/
    void SetScale(float _scale) { scale = _scale;  recomputeWorldTransform = true; }

	/**
	@brief　オブジェクトのクォータニオンを取得する
	@return	rotation（Quaternion型）
	*/
    const Quaternion& GetRotation() const { return rotation; }

	/**
	@brief　オブジェクトのクォータニオンを設定する
	@param	rotation（Quaternion型）
	*/
    void SetRotation(const Quaternion& _qotation) { rotation = _qotation;  recomputeWorldTransform = true; }

	/**
	@brief　オブジェクトの状態を取得する
	@return	state
	*/
	State GetState() const { return state; }

	/**
	@brief　オブジェクトの状態を設定する
	@param	state
	*/
	void SetState(State _state) { state = _state; }

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

	/**
	@brief　オブジェクトの右を表すベクトルを取得する
	@param	right(Vector3型)
	*/
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitY, rotation); }

	/**
	@brief　オブジェクトの上を表すベクトルを取得する
	@param	up(Vector3型)
	*/
	Vector3 GetUp() const { return Vector3::Transform(Vector3::UnitZ, rotation); }

	Tag GetTag() const { return tag; }

    virtual void OnCollision(GameObject& _hitObject) {}

    virtual void OnTrigger(GameObject& _triggerObject) {}

protected:
	//ゲームオブジェクトの状態
	State state;
	//ゲームオブジェクトのタグ
	Tag tag;

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

