//=============================================================================
//	@file	SphereCollider.h
//	@brief	球の当たり判定を行うコンポーネント
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

//-----------------------------------------------------------------------------
//	@brief	プリプロセッサ
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//	@brief	インクルード
//-----------------------------------------------------------------------------
#include "ColliderComponent.h"
#include "PhysicsWorld.h"

//-----------------------------------------------------------------------------
//	@brief	SphereColliderクラス
//-----------------------------------------------------------------------------
class SphereCollider final : public ColliderComponent
{
public:
//===================== publicのメンバ関数 ======================//

	/**
	@brief	コンストラクタ
	@param	アタッチするゲームオブジェクトのポインタ
	@param	他のオブジェクトと当たった時に呼ばれる関数ポインタ(GetOnCollisionFuncを呼ぶ)
	@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
	@param	当たり判定時に、めり込みから動かす処理の優先度を決める数値
	*/
	SphereCollider(GameObject* _owner, onCollisionFunc _func, int _updateOrder = 200, int _collisionOrder = 100);

	/**
	@brief	デストラクタ
	*/
	virtual ~SphereCollider();

	/**
	@brief	Transformのワールド変換
	*/
	virtual void OnUpdateWorldTransform() override;

	/**
	@brief	当たり判定に使うSphereの設定
	@param	オブジェクトの大きさに合わせたSphereの構造体
	*/
	void SetObjectSphere(const Sphere& _sphere) { objectSphere = _sphere; }

	/**
	@brief	当たり判定時に使うワールド空間でのSphereを取得する
	@return 中心をワールド座標に合わせたSphereの構造体
	*/
	Sphere GetWorldSphere() const { return worldSphere; }


private:
//===================== privateのメンバ変数 ======================//

	Sphere objectSphere;	//オブジェクトに設定する用の球（中心をオブジェクトの中心にする）
	Sphere worldSphere;		//当たり判定するときに使う球（中心をワールド座標の中心にする）

};

