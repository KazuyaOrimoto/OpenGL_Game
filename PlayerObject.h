#pragma once
#include "GameObject.h"

class MoveComponent;
class MainCamera;
class SphereCollider;
class AutoRunComponent;
class ObstacleObject;
class RotateComponent;
class DrilObject;

class PlayerObject : public GameObject
{
public:
	PlayerObject(Game* game);

	/**
	@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void UpdateGameObject(float argDaltaTime);

	RotateComponent* GetRotate() const { return rotate; }

    int GetTorque();

    void ResetTorque();
    bool CanMove();

private:
    MoveComponent* moveComp;
    MainCamera* camera;
    AutoRunComponent* autoRun;
	RotateComponent* rotate;
    SphereCollider* sphereCollider;
    DrilObject* dril;
};

