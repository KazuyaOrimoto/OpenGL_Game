//=============================================================================
//	@file	PlayerModel.cpp
//	@brief	プレイヤーのモデル関連の処理をする
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#include "PlayerModel.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "SphereCollider.h"
#include "ObstacleBox.h"
#include "InputSystem.h"
#include "HDRMeshComponent.h"
#include "SceneManager.h"
#include "MainCamera.h"
#include "EffekseerManager.h"

PlayerModel::PlayerModel(PlayerObject* _ownerObject)
	: GameObject()
	, ownerObject(_ownerObject)
	, animation(false)
	, animNum(0)
	, canJumping(false)
	, jump(false)
{
	SetParent(_ownerObject);
	meshComp = new HDRMeshComponent(this);
	meshComp->SetMesh(RENDERER->GetMesh("Assets/PlanePlayer.gpmesh"));
	meshComp->SetHDRColor(Vector3(0.7f, 0.7f, 0.7f));
	SetScale(3.0f);

	sphereCollider = new SphereCollider(this, GetOnCollisionFunc());
	sphereCollider->SetObjectSphere(Sphere(Vector3(0.0f, 0.0f, 0.0f), 1.0f));

	SetPosition(ownerObject->GetPosition());

	tag = Tag::Player;

	camera = new MainCamera(this);
	camera->SnapToIdeal();

	name = "BikeObject";
}

PlayerModel::~PlayerModel()
{
}

void PlayerModel::UpdateGameObject(float _deltaTime)
{
}

void PlayerModel::OnCollision(const GameObject& _hitObject)
{
	if (_hitObject.GetTag() == Tag::Boost)
	{
		ownerObject->playerSpeed += 200;
	}
	else if (_hitObject.GetTag() == Tag::Obstacle)
	{
		SceneManager::ChangeScene(SceneName::GameOver);
	}
}

void PlayerModel::GameObjectInput(const InputState & _state)
{
	if (_state.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) && _state.Keyboard.GetKeyState(SDL_SCANCODE_LEFT))
	{
		SetRotation(ownerObject->GetRotation());
	}
	else if (_state.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT))
	{
		Quaternion rot = ownerObject->GetRotation();
		float rad = Math::ToRadians(-10);
		Quaternion inc(Vector3::UnitX, rad);
		rot = Quaternion::Concatenate(rot, inc);
		SetRotation(rot);
	}
	else if (_state.Keyboard.GetKeyState(SDL_SCANCODE_LEFT))
	{
		Quaternion rot = ownerObject->GetRotation();
		float rad = Math::ToRadians(10);
		Quaternion inc(Vector3::UnitX, rad);
		rot = Quaternion::Concatenate(rot, inc);
		SetRotation(rot);
	}
	else if (_state.Controller.GetLAxisVec().x > 0.1)
	{
		Quaternion rot = ownerObject->GetRotation();
		float rad = Math::ToRadians(-10);
		Quaternion inc(Vector3::UnitX, rad);
		rot = Quaternion::Concatenate(rot, inc);
		SetRotation(rot);
	}
	else if (_state.Controller.GetLAxisVec().x < -0.1)
	{
		Quaternion rot = ownerObject->GetRotation();
		float rad = Math::ToRadians(10);
		Quaternion inc(Vector3::UnitX, rad);
		rot = Quaternion::Concatenate(rot, inc);
		SetRotation(rot);
	}
	else
	{
		SetRotation(ownerObject->GetRotation());
	}

	if (_state.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == ButtonState::Pressed)
	{
		EFFECT_MANAGER->PlayEffect(L"Effect/Fire.efk",ownerObject->GetPosition());
	}
}

bool PlayerModel::CanMove()
{
	if (jump)
	{
		return false;
	}
	else
	{
		return true;
	}
}
