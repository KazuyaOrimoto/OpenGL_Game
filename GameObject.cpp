#include "Game.h"
#include "Math.h"
#include "GameObject.h"
#include "Component.h"
#include "InputSystem.h"
//#include "GameObjectManager.h"

std::vector<GameObject*> GameObject::gameObjects;
std::vector<GameObject*> GameObject::pendingGameObjects;
bool GameObject::updatingGameObject = false;

/**
@param	ゲームクラスのポインタ
*/
GameObject::GameObject()
	: state(Active)
	, worldTransform()
	, position(Vector3::Zero)
	, scale(1.0f)
	, rotation(Quaternion::Identity)
	, recomputeWorldTransform(true)
	, parent(nullptr)
	, name("GameObject")
{
	GameObject::AddGameObject(this);
}

GameObject::~GameObject()
{
	GameObject::RemoveGameObject(this);
	while (!components.empty())
	{
		delete components.back();
	}
}

/**
@brief	フレーム毎の処理
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::Update(float _deltaTime)
{
	if (state == Active)
	{
		ComputeWorldTransform();

		UpdateComponents(_deltaTime);
		UpdateGameObject(_deltaTime);

		ComputeWorldTransform();
	}
}

/**
@brief	アタッチされてるコンポーネントのアップデート
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::UpdateComponents(float _deltaTime)
{
	for (auto itr : components)
	{
		if (itr->GetActive())
		{
			itr->Update(_deltaTime);
		}
	}
}

/**
@brief	ゲームオブジェクトのアップデート
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::UpdateGameObject(float _deltaTime)
{
}

void GameObject::ProcessInput(const InputState& _keyState)
{
	if (state == Active)
	{
		// First process input for components
		for (auto comp : components)
		{
			comp->ProcessInput(_keyState);
		}
		GameObjectInput(_keyState);
	}
}

void GameObject::GameObjectInput(const InputState& _keyState)
{
}

/**
@brief	コンポーネントを追加する
@param	追加するコンポーネントのポインタ
*/
void GameObject::AddComponent(Component * _component)
{
	int order = _component->GetUpdateOder();
	auto itr = components.begin();
	for (;
		itr != components.end();
		++itr)
	{
		if (order < (*itr)->GetUpdateOder())
		{
			break;
		}
	}
	components.insert(itr, _component);
}

/**
@brief	コンポーネントを削除する
@param	削除するコンポーネントのポインタ
*/
void GameObject::RemoveComponent(Component * _component)
{
	auto itr = std::find(components.begin(), components.end(), _component);
	if (itr != components.end())
	{
		components.erase(itr);
	}
}

/**
@brief	Transformのワールド変換
*/
void GameObject::ComputeWorldTransform()
{
	if (recomputeWorldTransform)
	{
		recomputeWorldTransform = false;
		worldTransform = Matrix4::CreateScale(scale);
		worldTransform *= Matrix4::CreateFromQuaternion(rotation);
		worldTransform *= Matrix4::CreateTranslation(position);

		for (auto itr : components)
		{
			itr->OnUpdateWorldTransform();
		}
	}
}

//void GameObject::UpdateGameObjects(float _deltaTime)
//{
//	if (Game::GetState() == Game::GameState::EGameplay)
//	{
//		updatingGameObject = true;
//		for (auto gameObject : gameObjects)
//		{
//			gameObject->Update(_deltaTime);
//		}
//		updatingGameObject = false;
//
//		for (auto pending : pendingGameObjects)
//		{
//			pending->ComputeWorldTransform();
//			gameObjects.emplace_back(pending);
//		}
//		pendingGameObjects.clear();
//	}
//}

//void GameObject::ProcessInputs(const InputState & _state)
//{
//	updatingGameObject = true;
//	for (auto gameObject : gameObjects)
//	{
//		gameObject->ProcessInput(_state);
//	}
//	updatingGameObject = false;
//}

void GameObject::AddGameObject(GameObject * _object)
{
	if (updatingGameObject)
	{
		pendingGameObjects.emplace_back(_object);
	}
	else
	{
		gameObjects.emplace_back(_object);
	}
}

void GameObject::RemoveGameObject(GameObject * _object)
{
	auto iter = std::find(pendingGameObjects.begin(), pendingGameObjects.end(), _object);
	if (iter != pendingGameObjects.end())
	{
		std::iter_swap(iter, pendingGameObjects.end() - 1);
		pendingGameObjects.pop_back();
	}

	iter = std::find(gameObjects.begin(), gameObjects.end(), _object);
	if (iter != gameObjects.end())
	{
		std::iter_swap(iter, gameObjects.end() - 1);
		gameObjects.pop_back();
	}
}

GameObject * GameObject::FindGameObject(Tag _tag)
{
	for (auto itr : gameObjects)
	{
		if (itr->GetTag() == _tag)
		{
			return itr;
		}
	}
	return nullptr;
}

std::vector<GameObject*> GameObject::FindGameObjects(Tag _tag)
{
	std::vector<GameObject*> ret;
	for (auto itr : gameObjects)
	{
		if (itr->GetTag() == _tag)
		{
			ret.push_back(itr);
		}
	}
	return ret;
}

