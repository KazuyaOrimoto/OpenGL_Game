#pragma once
#include "GameObject.h"
class WallObject :
	public GameObject
{
public:
	WallObject(Game* game,int i);
	~WallObject();

	/**
	@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float argDaltaTime) override;

private:
	GameObject* player;
};

