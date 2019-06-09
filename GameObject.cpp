#include "Game.h"
#include "Math.h"
#include "Property.h"
#include "GameObject.h"
#include "Component.h"

/**
@param	ゲームクラスのポインタ
*/
GameObject::GameObject(Game * argGame)
	: state(Active)
	, position(Vector2::Zero)
	, readOnlyPosition(position)
	, scale(1.0f)
	, rotation(0.0f)
	, game(argGame)
{
}

GameObject::~GameObject()
{
}

/**
@brief	フレーム毎の処理
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::Update(float argDaltaTime)
{
	if (state == Active)
	{
		
	}
}

/**
@brief	アタッチされてるコンポーネントのアップデート
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::UpdateComponents(float argDaltaTime)
{
}

/**
@brief	ゲームオブジェクトのアップデート
@param	最後のフレームを完了するのに要した時間
*/
void GameObject::UpdateGameObject(float argDaltaTime)
{
}

/**
@brief	コンポーネントを追加する
@param	追加するコンポーネントのポインタ
*/
void GameObject::AddComponent(Component * argComponent)
{
}

/**
@brief	コンポーネントを削除する
@param	削除するコンポーネントのポインタ
*/
void GameObject::RemoveComponent(Component * argComponent)
{
}
