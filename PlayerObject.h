#pragma once
#include "GameObject.h"

class MoveComponent;
class MeshComponent;
class MainCamera;
class SphereCollider;
class AutoRunComponent;

class PlayerObject : public GameObject
{
public:
	PlayerObject(Game* game);

	/**
	@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void UpdateGameObject(float argDaltaTime);

	/**
	@brief	�`�悷�邩�ǂ�����ݒ肷��
	@param	true : �`�悷�� , false : �`�悵�Ȃ�
	*/
    void SetVisible(bool visible);

private:
    MoveComponent* moveComp;
    MeshComponent* meshComp;
    SphereCollider* sphereCollider;
    MainCamera* camera;
    AutoRunComponent* autoRun;
};

