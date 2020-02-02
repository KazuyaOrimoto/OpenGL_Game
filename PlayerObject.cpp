#include "PlayerObject.h"
#include "Game.h"
#include "Renderer.h"
#include "MoveComponent.h"
#include "MainCamera.h"
#include "AutoRunComponent.h"
#include "RotateComponent.h"
#include "ObstacleManager.h"
#include "ObstacleObject.h"
#include "BikeObject.h"
#include "Math.h"
#include "ParticleComponent.h"
#include "Texture.h"
#include "imguiManager.h"
#include "EffectComponent.h"
#include "EffekseerManager.h"

PlayerObject::PlayerObject()
	:GameObject()
{
	SetPosition(Vector3(0.0f, 0.0f, 60.0f));

	OBSTACLE_MANAGER->AddPlayer(this);
	rotate = new RotateComponent(this);

	moveComp = new MoveComponent(this);
	moveComp->SetRightKey(SDL_SCANCODE_RIGHT);
	moveComp->SetLeftKey(SDL_SCANCODE_LEFT);
	moveComp->SetMaxStrafeSpeed(2400.0f);
	autoRun = new AutoRunComponent(this);
	playerSpeed = 1000;
	autoRun->SetForwardSpeed(playerSpeed);
	//camera = new MainCamera(this);
	//camera->SnapToIdeal();

	bike = new BikeObject(this);
	autoRun->SetDrilObject(bike);

	SetScale(10.0f);

	tag = Tag::Player;
	texture = RENDERER->GetTexture("Assets/fire.png");

	name = "Player";
	effect = new EffectComponent(this);
	effect->SetPosition(position);
	effect->LoadEffect("Effect/trail.efk",position);
	effect->Play();

}

/**
@brief	ゲームオブジェクトのアップデート
@param	最後のフレームを完了するのに要した時間
*/
void PlayerObject::UpdateGameObject(float _deltaTime)
{

	autoRun->SetForwardSpeed(playerSpeed);
	effect->SetPosition(position);

	// パーティクルのセット　これはあとでパーティクルエミッタクラス作りたい。

	Vector3 randV((rand() % 100) / 10.0f, (rand() % 100) / 10.0f, (rand() % 100) / 10.0f);
	Vector3 Velocity = randV * 0.1f;
	Velocity.x += -0.5f;
	Velocity.y += -0.5f;
	Velocity.z += 2.5f;

	// 後にパーティクル発生用クラス作成する
	// 3フレームに1回　パーティクル発生
	static int frame = 0;
	frame++;
	if (frame % 5 == 0)
	{
		//EFFECT_MANAGER->PlayEffect(L"Effect/Fire.efk", position);
		//effect = new EffectComponent(this);
		//effect->LoadEffect("Effect/Fire.efk", position);
		//effect->SetPosition(position);
		//effect->Play();
	}
}

bool PlayerObject::CanMove()
{
	return rotate->CanMove() && bike->CanMove();
}

#ifdef _DEBUG
void PlayerObject::ShowGameObject()
{
	ImGui::InputFloat("PlayerSpeed", &playerSpeed);

	ImGui::Text("Position   :   x = %f, y = %f, z = %f", position.x, position.y, position.z);
	ImGui::Text("Rotation   :   x = %f, y = %f, z = %f,w = %f", rotation.x, rotation.y, rotation.z, rotation.w);

}
#endif // _DEBUG

