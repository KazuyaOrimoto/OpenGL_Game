//=============================================================================
//	@file	BoostItem.h
//	@brief	�G���Ɖ�������I�u�W�F�N�g
//	@autor	���{ �a��
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
	@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
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

