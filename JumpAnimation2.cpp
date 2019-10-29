#include "JumpAnimation2.h"
#include "GameObject.h"


JumpAnimation2::JumpAnimation2(GameObject* _gameObject)
	:AnimationClip(_gameObject,20)
{
	rad = Math::ToRadians(-40);
	right = owner->GetRight();
}

JumpAnimation2::~JumpAnimation2()
{
}

void JumpAnimation2::Update(float deltaTime)
{
	//position = ownerObject->GetPosition() + GetUp() * 20.0f * (num3 - (animNum));
	//SetPosition(position);
	Vector3 playerPos = owner->GetParent()->GetPosition();
	Vector3 nextPos = playerPos + owner->GetUp() * 20.0f * (20 - animationCount);
	owner->SetPosition(nextPos);

	float r = Math::Lerp(rad, -(rad/2), ((float)animationCount / (float)animationChangeCount));
	Quaternion rot = owner->GetParent()->GetRotation();
	Quaternion inc(right, r);
	Quaternion NextRot = Quaternion::Concatenate(rot, inc);
	owner->SetRotation(NextRot);
}
