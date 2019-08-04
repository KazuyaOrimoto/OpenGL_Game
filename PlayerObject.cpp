#include "PlayerObject.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "MoveComponent.h"
#include "SphereCollider.h"
#include "MainCamera.h"
#include "AutoRunComponent.h"
#include "RotateComponent.h"
#include "ObstacleManager.h"
#include "ObstacleObject.h"

PlayerObject::PlayerObject(Game* game)
	:GameObject(game)
{
    meshComp = new MeshComponent(this);
    meshComp->SetMesh(RENDERER->GetMesh("Assets/Sphere.gpmesh"));
    SetPosition(Vector3(0.0f, 0.0f, 150.0f));
    SetScale(10.0f);

    OBSTACLE_MANAGER->AddPlayer(this);
	rotate = new RotateComponent(this);

    moveComp = new MoveComponent(this);
    moveComp->SetRightKey(SDL_SCANCODE_D);
    moveComp->SetLeftKey(SDL_SCANCODE_A);
    moveComp->SetMaxStrafeSpeed(1200.0f);
    autoRun = new AutoRunComponent(this);
    autoRun->SetForwardSpeed(1200.0f);
	camera = new MainCamera(this);
	camera->SnapToIdeal();

    sphereCollider = new SphereCollider(this);
    sphereCollider->SetObjectSphere(Sphere(Vector3(0.0f, 0.0f, 0.0f), 1.0f));

    tag = "Player";
}

/**
@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
@param	�Ō�̃t���[������������̂ɗv��������
*/
void PlayerObject::UpdateGameObject(float argDaltaTime)
{
}

/**
@brief	�`�悷�邩�ǂ�����ݒ肷��
@param	true : �`�悷�� , false : �`�悵�Ȃ�
*/
void PlayerObject::SetVisible(bool visible)
{
    meshComp->SetVisible(visible);
}

void PlayerObject::OnCollision(GameObject & argHitObject)
{
	if (argHitObject.GetTag() == "Obstacle")
	{
		//��Q���Ɠ����������̏���
		ObstacleObject* obstacle = dynamic_cast<ObstacleObject*>(&argHitObject);
		HitObstacle(*obstacle);
	}
}

void PlayerObject::HitObstacle(const ObstacleObject & argHitObstacle)
{
	//��Q���̕�������������
	if (rotate->GetTorque() < argHitObstacle.GetHardness())
	{
		meshComp->SetVisible(false);
	}
	//�����̕����͂�����������
	else
	{
		meshComp->SetVisible(true);
	}
}

