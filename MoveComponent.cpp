#include "MoveComponent.h"
#include "GameObject.h"


MoveComponent::MoveComponent(GameObject* owner, int updateOrder)
	:Component(owner,updateOrder)
	,angularSpeed(0.0f)
	,forwardSpeed(0.0f)
{

}


void MoveComponent::Update(float deltaTime)
{
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
		owner->SetPosition(pos);
	}
}
