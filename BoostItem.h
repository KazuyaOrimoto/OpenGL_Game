//=============================================================================
//	@file	BoostItem.h
//	@brief	触れると加速するオブジェクト
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#pragma once
#include "GameObject.h"
class BoostItem :
	public GameObject
{
public:
	BoostItem();
	~BoostItem();

	virtual void OnCollision(const GameObject& _hitObject) override;

	/**
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime) override;

	virtual void ResetBoostItem();
	virtual void UseBoostItem();

	void SetRot(float _rot);

private:
	class EffectComponent* comp;
	static GameObject* player;
	float rot;
};

