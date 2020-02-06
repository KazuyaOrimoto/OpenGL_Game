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
	@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime) override;

private:
	class EffectComponent* comp;
};

