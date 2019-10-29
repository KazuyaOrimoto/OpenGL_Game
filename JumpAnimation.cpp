#include "JumpAnimation.h"
#include "JumpAnimation2.h"
#include "GameObject.h"
#include "Math.h"


JumpAnimation::JumpAnimation(GameObject* _gameObject)
	:AnimationClip(_gameObject,20)
{
	SetNextAnimation(new JumpAnimation2(_gameObject));
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

}
