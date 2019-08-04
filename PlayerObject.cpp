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
@brief	ゲームオブジェクトのアップデート
@param	最後のフレームを完了するのに要した時間
*/
void PlayerObject::UpdateGameObject(float argDaltaTime)
{
}

/**
@brief	描画するかどうかを設定する
@param	true : 描画する , false : 描画しない
*/
void PlayerObject::SetVisible(bool visible)
{
    meshComp->SetVisible(visible);
}

void PlayerObject::OnCollision(GameObject & argHitObject)
{
	if (argHitObject.GetTag() == "Obstacle")
	{
		//障害物と当たった時の処理
		ObstacleObject* obstacle = dynamic_cast<ObstacleObject*>(&argHitObject);
		HitObstacle(*obstacle);
	}
}

void PlayerObject::HitObstacle(const ObstacleObject & argHitObstacle)
{
	//障害物の方が強かったら
	if (rotate->GetTorque() < argHitObstacle.GetHardness())
	{
		meshComp->SetVisible(false);
	}
	//自分の方が力が強かったら
	else
	{
		meshComp->SetVisible(true);
	}
}

