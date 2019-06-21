#pragma once

#include <cstdint>

class GameObject;

class Component
{
public:
	/**
	@param	アタッチするゲームオブジェクトのポインタ
	@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
	*/
	Component(GameObject* argOwner,int argUpdateOrder = 100);
	virtual ~Component();

	/**
	@brief	フレーム毎の処理
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void Update(float argDeltaTime);

	/**
	@brief	Transformのワールド変換
	*/
	virtual void OnUpdateWorldTransform() {}

	/**
	@brief	UpdateOrderを取得する
	@return UpdateOrder（数値が小さいほど早く更新される）
	*/
	int GetUpdateOder() { return updateOrder; }

protected:

	//アタッチしているゲームオブジェクトのポインタ
	GameObject* owner;			
	// コンポーネントの更新順番（数値が小さいほど早く更新される）
	int updateOrder;

};

