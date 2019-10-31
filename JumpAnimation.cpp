#include "JumpAnimation.h"
#include "JumpAnimation2.h"
#include "GameObject.h"
#include "MainCamera.h"

JumpAnimation::JumpAnimation(GameObject* _gameObject, MainCamera* _camera)
	:AnimationClip(_gameObject,20)
{
	SetNextAnimation(new JumpAnimation2(_gameObject, _camera));
	rad = Math::ToRadians(-40);
	right = owner->GetRight();
	camera = _camera;
}

JumpAnimation::~JumpAnimation()
{
}

void JumpAnimation::Update(float deltaTime)
{
	//ポジションのアニメーション
	Vector3 playerPos = owner->GetParent()->GetPosition();
	Vector3 nextPos = playerPos + owner->GetUp() * 20.0f * animationCount;
	owner->SetPosition(nextPos);

	//回転のアニメーション
	float r = Math::Lerp(0,rad,((float)animationCount/(float)animationChangeCount));
	Quaternion rot = owner->GetParent()->GetRotation();
	Quaternion inc(right, r);
	Quaternion NextRot = Quaternion::Concatenate(rot, inc);
	owner->SetRotation(NextRot);

	//カメラのアニメーション
	float vert = camera->GetVertDist();
	float horz = camera->GetHorzDist();

	camera->SetVertDist(vert - 25.0f);
	camera->SetHorzDist(horz - 25.0f);
}
