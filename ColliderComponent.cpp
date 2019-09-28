#include "ColliderComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "PhysicsWorld.h"

/**
@param	アタッチするゲームオブジェクトのポインタ
@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
*/
ColliderComponent::ColliderComponent(GameObject* _owner, int _updateOrder, int _collisionOrder)
	: Component(_owner, _updateOrder)
	, isTrigger(false)
	, collisionOrder(_collisionOrder)
{
}


ColliderComponent::~ColliderComponent()
{
}