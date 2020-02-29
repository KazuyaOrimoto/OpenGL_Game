//=============================================================================
//	@file	Component.cpp
//	@brief	ゲームオブジェクトにアタッチするコンポーネントの規定クラス
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "Component.h"
#include "GameObject.h"

/**
@param	アタッチするゲームオブジェクトのポインタ
@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
*/
Component::Component(GameObject* _owner, int _updateOrder)
	: owner(_owner)
	, updateOrder(_updateOrder)
	, active(true)
{
	owner->AddComponent(this);
}

/**
@brief	デストラクタ
*/
Component::~Component()
{
	owner->RemoveComponent(this);
}

/**
@param	最後のフレームを完了するのに要した時間
*/
void Component::Update(float _deltaTime)
{
}
