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
#include "DrilObject.h"
#include "Math.h"

PlayerObject::PlayerObject(Game* game)
	:GameObject(game)
{
    SetPosition(Vector3(0.0f, 0.0f, 150.0f));

    OBSTACLE_MANAGER->AddPlayer(this);
	rotate = new RotateComponent(this);

    moveComp = new MoveComponent(this);
    moveComp->SetRightKey(SDL_SCANCODE_D);
    moveComp->SetLeftKey(SDL_SCANCODE_A);
    moveComp->SetMaxStrafeSpeed(2400.0f);
    autoRun = new AutoRunComponent(this);
    autoRun->SetForwardSpeed(2400.0f);
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
@brief	ゲームオブジェクトのアップデート
@param	最後のフレームを完了するのに要した時間
*/
void PlayerObject::UpdateGameObject(float argDaltaTime)
{
}

bool PlayerObject::CanMove()
{
    return rotate->CanMove();
}
