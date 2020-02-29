//=============================================================================
//	@file	Component.h
//	@brief	ゲームオブジェクトにアタッチするコンポーネントの規定クラス
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
#include <cstdint>

//-----------------------------------------------------------------------------
//	@brief	前方宣言
//-----------------------------------------------------------------------------
class GameObject;

//-----------------------------------------------------------------------------
//	@brief	Componentクラス
//-----------------------------------------------------------------------------
class Component
{
public:
//===================== publicのメンバ関数 ======================//

	/**
	@brief	コンストラクタ
	@param	アタッチするゲームオブジェクトのポインタ
	@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
	*/
	Component(GameObject* _owner,int _updateOrder = 100);

	/**
	@brief	デストラクタ
	*/
	virtual ~Component();

	/**
	@brief	フレーム毎の処理
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void Update(float _deltaTime);

	/**
	@brief	入力処理
	@param	InputState構造体
	*/
	virtual void ProcessInput(const struct InputState& _state) {}

	/**
	@brief	Transformのワールド変換
	*/
	virtual void OnUpdateWorldTransform() {}

	/**
	@brief	UpdateOrderを取得する
	@return UpdateOrder（数値が小さいほど早く更新される）
	*/
	int GetUpdateOder() { return updateOrder; }

	/**
	@brief	アタッチしているゲームオブジェクトを取得する
	@return アタッチしているゲームオブジェクト
	*/
    GameObject* GetOwner() { return owner; }
	
	/**
	@brief	現在のActiveの状態を取得する
	@return Activeの状態(Active : true , 非Active : false)
	*/
	bool GetActive() { return active; }

	/**
	@brief	Activeの状態を設定する
	@param  Activeの状態(Active : true , 非Active : false)
	*/
	void SetActive(bool _active) { active = _active; }

protected:
//===================== protectedのメンバ変数 ======================//

	GameObject* owner;			// アタッチしているゲームオブジェクトのポインタ
	int updateOrder;			// コンポーネントの更新順番（数値が小さいほど早く更新される）
	bool active;				// このコンポーネントの更新をするかどうか

};

