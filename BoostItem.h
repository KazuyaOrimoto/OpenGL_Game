#pragma once
#include "GameObject.h"
class BoostItem :
	public GameObject
{
public:
	BoostItem();
	virtual ~BoostItem() override;

	virtual void OnCollision(const GameObject& _hitObject) override;

	/**
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime) override;

private:
	class EffectComponent* comp;
};

