#include "BikeObject.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "SphereCollider.h"
#include "ObstacleBox.h"
#include "InputSystem.h"
#include "jumpCheck.h"
#include "ObstacleCheck.h"
#include "ActionArea.h"
#include "AnimationComponent.h"
#include "AnimationController.h"
#include "PlayerAnimationController.h"
#include "HDRMeshComponent.h"

#include "MainCamera.h"

BikeObject::BikeObject(PlayerObject* _ownerObject)
	: GameObject()
	, ownerObject(_ownerObject)
	, animation(false)
	, animNum(0)
	, canJumping(false)
	, jump(false)
{
	SetParent(_ownerObject);
	HDRMeshComponent* m = new HDRMeshComponent(this);
	meshComp = m;
	meshComp->SetMesh(RENDERER->GetMesh("Assets/Bike.gpmesh"));
	Vector3 v = Vector3(0.5f, 0.5f, 0.5f);
	m->SetHDRColor(v);
	SetScale(7.0f);

	sphereCollider = new SphereCollider(this, GetOnCollisionFunc());
	sphereCollider->SetObjectSphere(Sphere(Vector3(0.0f, 0.0f, 0.0f), 1.0f));

	SetPosition(ownerObject->GetPosition());

	tag = Tag::Player;
	jumpCheck = new JumpCheck(this);
	obstacleCheck = new ObstacleCheck(this);
	action = new ActionArea(ownerObject);

	animationComp = new AnimationComponent(this);
	controller = new PlayerAnimationController(this,animationComp);

	camera = new MainCamera(this);
	camera->SnapToIdeal();

	name = "BikeObject";
}

BikeObject::~BikeObject()
{
}

void BikeObject::UpdateGameObject(float _deltaTime)
{
	ActionDetermining();
	Animation();
}

void BikeObject::OnCollision(const GameObject& _hitObject)
{
	if (_hitObject.GetTag() == Tag::Obstacle)
	{
		if (jump)
		{
			return;
		}
		//障害物と当たった時の処理
		//animation = true;
		//meshComp->SetVisible(false);
	}
}

void BikeObject::GameObjectInput(const InputState & _state)
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
	else if (_state.Keyboard.GetKeyState(SDL_SCANCODE_SPACE))
	{
		if (canJumping && !jump)
		{
			controller->Jump();
			animationComp->SetActive(false);
			jump = true;
			sphereCollider->CollisionPause();
			SetRotation(ownerObject->GetRotation());
		}
	}
	else
	{
		SetRotation(ownerObject->GetRotation());
	}

}

bool BikeObject::CanMove()
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

void BikeObject::Animation()
{
	if (jump)
	{
		if (animationComp->AnimationEnd())
		{
			animNum = 0;
			jump = false;
			sphereCollider->CollisionActive();
		}
	}
}

/**
@brief	アクションを決定する
*/
void BikeObject::ActionDetermining()
{
	//ジャンプできるかどうか
	bool canJump = jumpCheck->CanJump() && obstacleCheck->OnObstacle();
	//ジャンプ中でないとき
	if (!canJumping)
	{
		//ジャンプできるとき
		if (canJump)
		{
			canJumping = true;
			action->CanJump();
		}
	}
	//ジャンプできないとき
	if (!canJump)
	{
		action->CanNotJump();
		canJumping = false;
	}
	if (jump && !canJump)
	{
		animationComp->SetActive(true);
	}
}
