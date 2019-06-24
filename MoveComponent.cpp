#include "MoveComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"

MoveComponent::MoveComponent(GameObject* owner, int updateOrder)
	:Component(owner, updateOrder)
	, angularSpeed(0.0f)
	, pitchSpeed(0.0f)
	, forwardSpeed(0.0f)
	, strafeSpeed(0.0f)
	, maxPitch(Math::Pi / 3.0f)
{

}

void MoveComponent::Update(float deltaTime)
{

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

		Game* game = owner->GetGame();
		game->GetRenderer()->SetViewMatrix(view);
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



	if (!Math::NearZero(forwardSpeed))
	{
		Vector3 pos = owner->GetPosition();
		pos += owner->GetForward() * forwardSpeed * deltaTime;
		pos += owner->GetRight() * strafeSpeed * deltaTime;
		owner->SetPosition(pos);
	}

	if (!Math::NearZero(strafeSpeed))
	{
		Vector3 pos = owner->GetPosition();
		pos += owner->GetRight() * strafeSpeed * deltaTime;
		owner->SetPosition(pos);
	}
}
