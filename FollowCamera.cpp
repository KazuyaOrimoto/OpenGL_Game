#include "FollowCamera.h"
#include "GameObject.h"
#include "InputSystem.h"

FollowCamera::FollowCamera(GameObject* _owner)
	:CameraComponent(_owner)
	, horzDist(350.0f)
	, vertDist(150.0f)
	, targetDist(100.0f)
	, springConstant(64.0f)
{
}

void FollowCamera::Update(float _deltaTime)
{
	if (!Math::NearZero(angularSpeed))
	{
		Quaternion rot = owner->GetRotation();
		float angle = angularSpeed * _deltaTime;
		// Create quaternion for incremental rotation
		// (Rotate about up axis)
		Quaternion inc(Vector3::UnitZ, angle);
		// Concatenate old and new quaternion
		rot = Quaternion::Concatenate(rot, inc);
		owner->SetRotation(rot);
	}

	CameraComponent::Update(_deltaTime);

	float dampening = 2.0f * Math::Sqrt(springConstant);

	Vector3 idealPos = ComputeCameraPos();

	Vector3 diff = actualPos - idealPos;

	Vector3 acel = -springConstant * diff - dampening * velocity;

	velocity += acel * _deltaTime;

	actualPos += velocity * _deltaTime;

	Vector3 target = owner->GetPosition() + owner->GetForward() * targetDist;

	Matrix4 view = Matrix4::CreateLookAt(actualPos,target,Vector3::UnitZ);

	SetViewMatrix(view);
}

void FollowCamera::ProcessInput(const InputState & _state)
{
	float forwardSpeed = 0.0f;
	angularSpeed = 0.0f;
	if (_state.Keyboard.GetKeyValue(SDL_Scancode(mForwardKey)))
	{
		forwardSpeed += 1.0f;
	}
	if (_state.Keyboard.GetKeyValue(SDL_Scancode(mBackKey)))
	{
		forwardSpeed -= 1.0f;
	}
	if (_state.Keyboard.GetKeyValue(SDL_Scancode(rightKey)))
	{
		angularSpeed += Math::Pi;
	}
	if (_state.Keyboard.GetKeyValue(SDL_Scancode(leftKey)))
	{
		angularSpeed -= Math::Pi;
	}

	if (!Math::NearZero(forwardSpeed))
	{
		horzDist = 500.0f;
	}
	else
	{
		horzDist = 350.0f;
	}
}

void FollowCamera::SnapToIdeal()
{
	actualPos = ComputeCameraPos();

	velocity = Vector3::Zero;

	Vector3 target = owner->GetPosition() + owner->GetForward() * targetDist;

	Matrix4 view = Matrix4::CreateLookAt(actualPos,target,Vector3::UnitZ);

	SetViewMatrix(view);
}

Vector3 FollowCamera::ComputeCameraPos() const
{
	Vector3 cameraPos = owner->GetPosition();

	cameraPos -= owner->GetForward() * horzDist;

	cameraPos += Vector3::UnitZ * vertDist;

	return cameraPos;
}
