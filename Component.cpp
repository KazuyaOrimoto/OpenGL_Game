#include "Component.h"
#include "GameObject.h"

/**
@param	アタッチするゲームオブジェクトのポインタ
@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
*/
Component::Component(GameObject* argOwner, int argUpdateOrder)
	: owner(argOwner)
	, updateOrder(argUpdateOrder)
{
	owner->AddComponent(this);
}

Component::~Component()
{
	owner->RemoveComponent(this);
}

/**
@param	最後のフレームを完了するのに要した時間
*/
void Component::Update(float argDeltaTime)
{
}
