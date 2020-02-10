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
#include "Texture.h"
#include "imguiManager.h"
#include "EffectComponent.h"
#include "EffekseerManager.h"
#include "InputSystem.h"
#include "SceneManager.h"

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
	playerSpeed = 3000;
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
	effect->LoadEffect("Effect/trail.efk", position);
	effect->Play();

}

/**
@brief	ゲームオブジェクトのアップデート
@param	最後のフレームを完了するのに要した時間
*/
void PlayerObject::UpdateGameObject(float _deltaTime)
{
	autoRun->SetForwardSpeed(playerSpeed);
	effect->SetPosition(position + (GetForward() * -100) + (GetUp() * 15));

	GameObject* wall = nullptr;
	wall = GameObject::FindGameObject(Tag::Wall);

	//壁が無くなってクリア演出を呼ぶタイミング
	if (wall == nullptr)
	{
		SceneManager::ChangeScene(SceneName::GameClear);
	}

}

void PlayerObject::GameObjectInput(const InputState & _state)
{
	if (_state.Keyboard.GetKeyState(SDL_SCANCODE_SPACE))
	{
		effect->Stop();
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

