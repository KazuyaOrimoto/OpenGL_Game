#include "MoveComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"
#include "InputSystem.h"
#include "PlayerObject.h"

MoveComponent::MoveComponent(GameObject* owner, int updateOrder)
	:Component(owner, updateOrder)
	, forwardSpeed(0.0f)
	, starafeSpeed(0.0f)
	, maxForwardSpeed(0.0f)
	, maxStrafeSpeed(0.0f)
{
    player = dynamic_cast<PlayerObject*>(owner);
}

void MoveComponent::Update(float deltaTime)
{
    if (player->CanMove())
    {
        if (!Math::NearZero(forwardSpeed) || !Math::NearZero(starafeSpeed))
        {
            Vector3 pos = owner->GetPosition();
            pos += owner->GetForward() * forwardSpeed * deltaTime;
            pos += owner->GetRight() * starafeSpeed * deltaTime;
            owner->SetPosition(pos);
        }
    }

}

void MoveComponent::ProcessInput(const InputState & state)
{
	// Calculate forward speed for MoveComponent
	forwardSpeed = 0.0f;
	starafeSpeed = 0.0f;

	if (state.Keyboard.GetKeyValue(SDL_Scancode(mForwardKey)))
	{
		forwardSpeed += maxForwardSpeed;
	}
	if (state.Keyboard.GetKeyValue(SDL_Scancode(mBackKey)))
	{
		forwardSpeed -= maxForwardSpeed;
	}
	if (state.Keyboard.GetKeyValue(SDL_Scancode(rightKey)))
	{
		starafeSpeed += maxStrafeSpeed;
	}
	if (state.Keyboard.GetKeyValue(SDL_Scancode(leftKey)))
	{
		starafeSpeed -= maxStrafeSpeed;
	}
}
