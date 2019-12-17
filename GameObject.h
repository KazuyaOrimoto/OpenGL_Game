#pragma once
#include <vector>
#include <functional>
#include "Math.h"

class Game;
class Vector3;
class Matrix4;
class Component;
struct InputState;

enum Tag
{
	NoneTag,
	Player,
	Obstacle,
	JumpingObstacle,
	Wall,
	CheckArea
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
	GameObject();
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

protected:
    std::function<void(GameObject&)> GetOnCollisionFunc() { return std::bind(&GameObject::OnCollision, this, std::placeholders::_1); }
    virtual void OnCollision(const GameObject& _hitObject) {}

    //virtual void OnTrigger(GameObject& _triggerObject) {}
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

	//子のゲームオブジェクト
	std::vector <GameObject*>childObjects;
	//親のゲームオブジェクト
	GameObject* parent;

	std::string name;

public:
	//-----------------------------------------------------------------------------
	//							Getter・Setter群
	//-----------------------------------------------------------------------------
	/**
	@brief　オブジェクトのポジションを取得する
	@return	position
	*/
	const Vector3& GetPosition() const { return position; }

	/**
	@brief　オブジェクトのポジションを設定する
	@param	position
	*/
	virtual void SetPosition(const Vector3& _pos) { position = _pos; recomputeWorldTransform = true; }

	/**
	@brief　オブジェクトのスケールを取得する
	@return	scale
	*/
	float GetScale() const { return scale; }

	/**
	@brief　オブジェクトのスケールを設定する
	@param	scale
	*/
	virtual void SetScale(float _scale) { scale = _scale;  recomputeWorldTransform = true; }

	/**
	@brief　オブジェクトのクォータニオンを取得する
	@return	rotation（Quaternion型）
	*/
	const Quaternion& GetRotation() const { return rotation; }

	/**
	@brief　オブジェクトのクォータニオンを設定する
	@param	rotation（Quaternion型）
	*/
	virtual void SetRotation(const Quaternion& _qotation) { rotation = _qotation;  recomputeWorldTransform = true; }

	/**
	@brief	子のオブジェクトを設定する
	@param	設定するゲームオブジェクト
	*/
	void SetChild(GameObject* _object) { childObjects.emplace_back(_object); }

	/**
	@brief	親のオブジェクトの設定
	@param	設定するゲームオブジェクト
	*/
	void SetParent(GameObject* _object) { parent = _object; _object->SetChild(this); }

	GameObject* GetParent() { return parent; }

	/**
	@brief　オブジェクトの状態を取得する
	@return	state
	*/
	State GetState() const { return state; }

	/**
	@brief　オブジェクトの状態を設定する
	@return	state
	*/
	virtual void SetState(State _state) { state = _state; }

	/**
	@brief　オブジェクトのワールド行列を取得する
	@return	worldTransform
	*/
	const Matrix4& GetWorldTransform() const { return worldTransform; }

	/**
	@brief　オブジェクトの前方を表すベクトルを取得する
	@return	forward(Vector3型)
	*/
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, rotation); }

	/**
	@brief　オブジェクトの右を表すベクトルを取得する
	@return	right(Vector3型)
	*/
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitY, rotation); }

	/**
	@brief　オブジェクトの上を表すベクトルを取得する
	@return	up(Vector3型)
	*/
	Vector3 GetUp() const { return Vector3::Transform(Vector3::UnitZ, rotation); }

	/**
	@brief	オブジェクトのタグを取得する
	@return	オブジェクトのタグ
	*/
	Tag GetTag() const { return tag; }

	static GameObject* FindGameObject(Tag _tag);
	static std::vector<GameObject*> FindGameObjects(Tag _tag);

	/**
	@brief  ゲームオブジェクトの追加
	@param	追加するGameObjectクラスのポインタ
	*/
	static void AddGameObject(GameObject* _object);

	/**
	@brief  ゲームオブジェクトの削除
	@param	削除するGameObjectクラスのポインタ
	*/
	static void RemoveGameObject(GameObject* _object);

private:

	/**
	@brief  ゲームオブジェクトのアップデート処理
	*/
	friend void UpdateGameObjects(float _deltaTime);

	/**
	@brief  ゲームオブジェクトの入力処理
	*/
	friend void ProcessInputs(const InputState& _state);

	//ゲームオブジェクトのポインタの可変長コンテナ
	static std::vector<GameObject*> gameObjects;
	//Update中に追加されたゲームオブジェクトのポインタを一時的に保存する可変長コンテナ
	static std::vector<GameObject*> pendingGameObjects;

	//Update中かどうか
	static bool updatingGameObject;

private:
#ifdef _DEBUG
		friend class imguiManager;
		bool view;
#endif // _DEBUG

};

