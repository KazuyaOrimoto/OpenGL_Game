#include "FPSCameraInput.h"
#include "GameObject.h"
#include "InputSystem.h"

FPSCameraInput::FPSCameraInput(class GameObject* owner)
	:MoveComponent(owner)
	, mForwardKey(0)
	, mBackKey(0)
	, mClockwiseKey(0)
	, mCounterClockwiseKey(0)
	, rightKey(0)
	, leftKey(0)
{
}


void FPSCameraInput::ProcessInput(const InputState & state)
{
	
	// Calculate forward speed for MoveComponent
	float forwardSpeed = 0.0f;
	float starafeSpeed = 0.0f;

	if (state.Keyboard.GetKeyValue(SDL_Scancode(mForwardKey)))
	{
		forwardSpeed += mMaxForwardSpeed;
	}
	if (state.Keyboard.GetKeyValue(SDL_Scancode(mBackKey)))
	{
		forwardSpeed -= mMaxForwardSpeed;
	}
	if (state.Keyboard.GetKeyValue(SDL_Scancode(rightKey)))
	{
		starafeSpeed += mMaxForwardSpeed;
	}
	if (state.Keyboard.GetKeyValue(SDL_Scancode(leftKey)))
	{
		starafeSpeed -= mMaxForwardSpeed;
	}
	SetForwardSpeed(forwardSpeed);
	SetStrafeSpeed(starafeSpeed);

	// Calculate angular speed for MoveComponent
	const Vector2 mouse = state.Mouse.GetPosition();
	const int maxMouseSpeed = 100;
	const float maxAngularSpeed = Math::Pi * 8;
	float angularSpeed = 0.0f;
	if (mouse.x != 0)
	{
		// Convert to ~[-1.0, 1.0]
		angularSpeed = static_cast<float>(mouse.x) / maxMouseSpeed;
		// Multiply by rotation/sec
		angularSpeed *= maxAngularSpeed;
	}
	SetAngularSpeed(angularSpeed / 100);

	const float maxPitchSpeed = Math::Pi * 8;
	float pitchSpeed = 0.0f;
	if (mouse.y != 0)
	{
		// Convert to ~[-1.0, 1.0]
		pitchSpeed = static_cast<float>(mouse.y) / maxMouseSpeed;
		pitchSpeed *= maxPitchSpeed;
	}
	SetPitchSpeed(pitchSpeed / 100);
}
