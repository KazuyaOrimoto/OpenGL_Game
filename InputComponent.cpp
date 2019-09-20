#include "InputComponent.h"
#include "GameObject.h"
#include "InputSystem.h"

InputComponent::InputComponent(GameObject* _owner)
	:MoveComponent(_owner)
	, mForwardKey(0)
	, mBackKey(0)
	, mClockwiseKey(0)
	, mCounterClockwiseKey(0)
{
}

void InputComponent::ProcessInput(const InputState& _state)
{
	// Calculate forward speed for MoveComponent
	float forwardSpeed = 0.0f;

	if (_state.Keyboard.GetKeyValue(SDL_Scancode(mForwardKey)))
	{
		forwardSpeed += mMaxForwardSpeed;
	}
	if (_state.Keyboard.GetKeyValue(SDL_Scancode(mBackKey)))
	{
		forwardSpeed -= mMaxForwardSpeed;
	}

	// Calculate angular speed for MoveComponent
	float angularSpeed = 0.0f;
	if (_state.Keyboard.GetKeyValue(SDL_Scancode(mClockwiseKey)))
	{
		angularSpeed += mMaxAngularSpeed;
	}
	if (_state.Keyboard.GetKeyValue(SDL_Scancode(mCounterClockwiseKey)))
	{
		angularSpeed -= mMaxAngularSpeed;
	}
	//SetAngularSpeed(angularSpeed);
}

