//=============================================================================
//	@file	CameraComponent.cpp
//	@brief	カメラの機能を持つコンポーネントの基底クラス
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "CameraComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "GameObject.h"

/**
@brief	コンストラクタ
@param	アタッチするゲームオブジェクトのポインタ
@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
*/
CameraComponent::CameraComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner,_updateOrder)
{
}

/**
@brief	フレーム毎の処理
@param	最後のフレームを完了するのに要した時間
*/
void CameraComponent::Update(float _deltaTime)
{
	Vector3 cameraPos = owner->GetPosition();

	Quaternion q(owner->GetRight(), 0.0f);

	Vector3 viewForward = Vector3::Transform(owner->GetForward(), q);

	Vector3 target = cameraPos + viewForward * 100.0f;

	Vector3 up = Vector3::Transform(Vector3::UnitZ, q);

	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);

	RENDERER->SetViewMatrix(view);
}

/**
@brief	ビュー行列を設定する
@param	設定するビュー行列
*/
void CameraComponent::SetViewMatrix(const Matrix4 & _view)
{
	RENDERER->SetViewMatrix(_view);
}


