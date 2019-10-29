#include "JumpAnimation.h"
#include "JumpAnimation2.h"
#include "GameObject.h"

JumpAnimation::JumpAnimation(GameObject* _gameObject)
	:AnimationClip(_gameObject,20)
{
	SetNextAnimation(new JumpAnimation2(_gameObject));
	rad = Math::ToRadians(-40);
	right = owner->GetRight();
}

JumpAnimation::~JumpAnimation()
{
}

void JumpAnimation::Update(float deltaTime)
{
	//position = ownerObject->GetPosition() + GetUp() * 20.0f;
	//SetPosition(position);
	Vector3 playerPos = owner->GetParent()->GetPosition();
	Vector3 nextPos = playerPos + owner->GetUp() * 20.0f * animationCount;
	owner->SetPosition(nextPos);

	float r = Math::Lerp(0,rad,((float)animationCount/(float)animationChangeCount));
	Quaternion rot = owner->GetParent()->GetRotation();
	Quaternion inc(right, r);
	Quaternion NextRot = Quaternion::Concatenate(rot, inc);
	owner->SetRotation(NextRot);
}
