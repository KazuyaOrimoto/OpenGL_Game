#pragma once

#include "Property.h"
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
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void Update(float argDeltaTime);

	virtual void ProcessInput(const uint8_t* keyState) {}

	virtual void OnUpdateWorldTransform() {}

	cpp_module::ReadOnlyProperty<int> readOnlyUpdateOrder;
protected:
	GameObject* owner;			//アタッチしているゲームオブジェクトのポインタ
	int updateOrder;			//コンポーネントの更新順番（数値が小さいほど早く更新される）

};

