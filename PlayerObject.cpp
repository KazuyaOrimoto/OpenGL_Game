#include "PlayerObject.h"
#include "Game.h"
#include "Renderer.h"
#include "MoveComponent.h"
#include "SphereCollider.h"
#include "MainCamera.h"
#include "AutoRunComponent.h"
#include "RotateComponent.h"
#include "ObstacleManager.h"
#include "ObstacleObject.h"
#include "WallManager.h"
#include "DrilObject.h"
#include "Math.h"

PlayerObject::PlayerObject(Game* game)
	:GameObject(game)
{

    SetPosition(Vector3(0.0f, 0.0f, 150.0f));

    OBSTACLE_MANAGER->AddPlayer(this);
	WALL_MANAGER->AddPlayer(this);
	rotate = new RotateComponent(this);

    moveComp = new MoveComponent(this);
    moveComp->SetRightKey(SDL_SCANCODE_D);
    moveComp->SetLeftKey(SDL_SCANCODE_A);
    moveComp->SetMaxStrafeSpeed(1200.0f);
    autoRun = new AutoRunComponent(this);
    autoRun->SetForwardSpeed(1200.0f);
	camera = new MainCamera(this);
	camera->SnapToIdeal();


    dril = new DrilObject(game, this);
    autoRun->SetDrilObject(dril);

    SetScale(10.0f);

    sphereCollider = new SphereCollider(this);
    sphereCollider->SetObjectSphere(Sphere(Vector3(0.0f, 0.0f, 0.0f), 10.0f));
    tag = "Player";

}

/**
@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
@param	�Ō�̃t���[������������̂ɗv��������
*/
void PlayerObject::UpdateGameObject(float argDaltaTime)
{
}


int PlayerObject::GetTorque()
{
    return rotate->GetTorque();;
}

void PlayerObject::ResetTorque()
{
    rotate->ResetTorque();
}

bool PlayerObject::CanMove()
{
    return rotate->CanMove();
}
