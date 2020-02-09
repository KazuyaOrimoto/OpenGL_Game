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

