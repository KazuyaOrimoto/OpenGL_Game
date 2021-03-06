﻿//=============================================================================
//	@file	MoveComponent.cpp
//	@brief	移動をするコンポーネント
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#include "MoveComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"
#include "InputSystem.h"
#include "PlayerObject.h"

MoveComponent::MoveComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
	, forwardSpeed(0.0f)
	, starafeSpeed(0.0f)
	, maxForwardSpeed(0.0f)
	, maxStrafeSpeed(0.0f)
{
    player = dynamic_cast<PlayerObject*>(owner);
}

void MoveComponent::Update(float _deltaTime)
{
	if (_deltaTime > 0.02)
	{
		return;
	}
    if (player->CanMove())
    {
        if (!Math::NearZero(forwardSpeed) || !Math::NearZero(starafeSpeed))
        {
            Vector3 pos = owner->GetPosition();
            pos += owner->GetForward() * forwardSpeed * _deltaTime;
            pos += owner->GetRight() * starafeSpeed * _deltaTime;
            owner->SetPosition(pos);
        }
    }

}

void MoveComponent::ProcessInput(const InputState & _state)
{
	// Calculate forward speed for MoveComponent
	forwardSpeed = 0.0f;
	starafeSpeed = 0.0f;

	if (_state.Keyboard.GetKeyValue(SDL_Scancode(mForwardKey)))
	{
		forwardSpeed += maxForwardSpeed;
	}
	if (_state.Keyboard.GetKeyValue(SDL_Scancode(mBackKey)))
	{
		forwardSpeed -= maxForwardSpeed;
	}
	if (_state.Keyboard.GetKeyValue(SDL_Scancode(rightKey)))
	{
		starafeSpeed += maxStrafeSpeed;
	}
	if (_state.Keyboard.GetKeyValue(SDL_Scancode(leftKey)))
	{
		starafeSpeed -= maxStrafeSpeed;
	}
	float direction = _state.Controller.GetLAxisVec().x;
	if (direction > 0.1)
	{
		starafeSpeed += maxStrafeSpeed * direction;
	}
	if (direction < -0.1)
	{
		starafeSpeed -= maxStrafeSpeed * -direction;
	}
}
