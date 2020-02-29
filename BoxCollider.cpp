//=============================================================================
//	@file	BoxCollider.h
//	@brief	ボックスの当たり判定を行うコンポーネント
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "BoxCollider.h"
#include "Math.h"
#include "GameObject.h"
#include "Collision.h"
#include "Game.h"

/**
@brief	コンストラクタ
@param	アタッチするゲームオブジェクトのポインタ
@param	他のオブジェクトと当たった時に呼ばれる関数ポインタ(GetOnCollisionFuncを呼ぶ)
@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
@param	当たり判定の優先順位(めり込み補正をする場合値が小さいほうを動かす)
*/
BoxCollider::BoxCollider(GameObject* _owner, onCollisionFunc _func, int _updateOrder, int _collisionOrder)
	: ColliderComponent(_owner, _updateOrder, _collisionOrder)
	, objectBox({Vector3::Zero,Vector3::Zero})
	, worldBox({ Vector3::Zero,Vector3::Zero})
{
	PHYSICS->AddBox(this,_func);
}

/**
@brief	デストラクタ
*/
BoxCollider::~BoxCollider()
{
	PHYSICS->RemoveBox(this);
}

/**
@brief	Transformのワールド変換
*/
void BoxCollider::OnUpdateWorldTransform()
{
    worldBox.min = (objectBox.min * owner->GetScale()) + owner->GetPosition();
    worldBox.max = (objectBox.max * owner->GetScale()) + owner->GetPosition();

	PHYSICS->HitCheck(this);
}

