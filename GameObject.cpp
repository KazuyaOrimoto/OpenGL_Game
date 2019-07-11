#include "Game.h"
#include "Math.h"
#include "GameObject.h"
#include "Component.h"
#include "InputSystem.h"
#include "GameObjectManager.h"

/**
@param	ゲームクラスのポインタ
*/
GameObject::GameObject(Game * argGame)
	: state(Active)
	, worldTransform()
	, position(Vector3::Zero)
	, scale(1.0f)
	, rotation(Quaternion::Identity)
	, recomputeWorldTransform(true)
	, game(argGame)
{
	GAME_OBJECT_MANAGER->AddGameObject(this);
}

GameObject::~GameObject()
{
    GAME_OBJECT_MANAGER->RemoveGameObject(this);
	while (!components.empty())
	{
		delete components.back();
	}
}

/**
@brief	フレーム毎の処理
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::Update(float argDaltaTime)
{
	if (state == Active)
	{
		ComputeWorldTransform();

		UpdateComponents(argDaltaTime);
		UpdateGameObject(argDaltaTime);

		ComputeWorldTransform();

	}
}

/**
@brief	アタッチされてるコンポーネントのアップデート
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::UpdateComponents(float argDaltaTime)
{
	for (auto itr : components)
	{
		itr->Update(argDaltaTime);
	}
}

/**
@brief	ゲームオブジェクトのアップデート
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::UpdateGameObject(float argDaltaTime)
{
}

void GameObject::ProcessInput(const InputState& keyState)
{
	if (state == Active)
	{
		// First process input for components
		for (auto comp : components)
		{
			comp->ProcessInput(keyState);
		}
		GameObjectInput(keyState);
	}
}

void GameObject::GameObjectInput(const InputState& keyState)
{
}

/**
@brief	コンポーネントを追加する
@param	追加するコンポーネントのポインタ
*/
void GameObject::AddComponent(Component * argComponent)
{
	int order = argComponent->GetUpdateOder();
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
	components.insert(itr,argComponent);
}

/**
@brief	コンポーネントを削除する
@param	削除するコンポーネントのポインタ
*/
void GameObject::RemoveComponent(Component * argComponent)
{
	auto itr = std::find(components.begin(),components.end(),argComponent);
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
