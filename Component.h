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
	Component(GameObject* _owner,int _updateOrder = 100);
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

    GameObject* GetOwner() { return owner; };


protected:

	//アタッチしているゲームオブジェクトのポインタ
	GameObject* owner;			
	// コンポーネントの更新順番（数値が小さいほど早く更新される）
	int updateOrder;

};

