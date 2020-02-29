//=============================================================================
//	@file	TitlePlayer.h
//	@brief	�^�C�g���̃V�[���̃v���C���[�̃I�u�W�F�N�g
//	@autor	���{ �a��
//	@date	2020/02/29
//=============================================================================

#pragma once
#include "GameObject.h"
class TitlePlayer :
	public GameObject
{
public:
	TitlePlayer();
	~TitlePlayer();

	/**
	@brief	�t���[�����̏���
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void UpdateGameObject(float _deltaTime) override;

private:

	class HDRMeshComponent* meshComp;
	class TitleCamera* camera;
	class AutoRunComponent* autoRun;
	class EffectComponent* effect;

};

