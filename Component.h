#pragma once

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

	/**
	@return コンポーネントの更新順番（数値が小さいほど早く更新される）
	*/
	int GetUpdateOrder() const { return updateOrder; }

protected:
	GameObject* owner;			//アタッチしているゲームオブジェクトのポインタ
	int updateOrder;			//コンポーネントの更新順番（数値が小さいほど早く更新される）

};

