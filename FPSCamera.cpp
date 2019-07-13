#include "FPSCamera.h"
#include "GameObject.h"
#include "InputSystem.h"
#include "Game.h"
#include "Renderer.h"

FPSCamera::FPSCamera(GameObject * argOwner)
	:CameraComponent(argOwner)
	, angularSpeed(0.0f)
	, maxAngularSpeed(Math::Pi * 4)
	, pitch(0.0f)
	, pitchSpeed(0.0f)
	, maxPitch(Math::Pi / 3.0f)
	, maxPitchSpeed(Math::Pi * 8)
{
}

void FPSCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);
	if (!Math::NearZero(pitchSpeed))
	{
		Vector3 cameraPos = owner->GetPosition();

		pitch += pitchSpeed * deltaTime;

		pitch = Math::Clamp(pitch, -maxPitch, maxPitch);

		Quaternion q(owner->GetRight(), pitch);

		Vector3 viewForward = Vector3::Transform(owner->GetForward(), q);

		Vector3 target = cameraPos + viewForward * 100.0f;

		Vector3 up = Vector3::Transform(Vector3::UnitZ, q);

		Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);

		RENDERER->SetViewMatrix(view);
	}

	if (!Math::NearZero(angularSpeed))
	{
		Quaternion rot = owner->GetRotation();
		float angle = angularSpeed * deltaTime;
		// Create quaternion for incremental rotation
		// (Rotate about up axis)
		Quaternion inc(Vector3::UnitZ, angle);
		// Concatenate old and new quaternion
		rot = Quaternion::Concatenate(rot, inc);
		owner->SetRotation(rot);
	}
}

void FPSCamera::ProcessInput(const InputState & state)
{
	// Calculate angular speed for MoveComponent
	const Vector2 mouse = state.Mouse.GetPosition();
	const int maxMouseSpeed = 500;
	angularSpeed = 0.0f;
	if (mouse.x != 0)
	{
		// Convert to ~[-1.0, 1.0]
		angularSpeed = static_cast<float>(mouse.x) / maxMouseSpeed;
		// Multiply by rotation/sec
		angularSpeed *= maxAngularSpeed;
	}

	pitchSpeed = 0.0f;
	if (mouse.y != 0)
	{
		// Convert to ~[-1.0, 1.0]
		pitchSpeed = static_cast<float>(mouse.y) / maxMouseSpeed;
		pitchSpeed *= -maxPitchSpeed;
	}
}
