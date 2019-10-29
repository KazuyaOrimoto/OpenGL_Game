#include "AnimationComponent.h"
#include "GameObject.h"
#include "AnimationClip.h"


AnimationComponent::AnimationComponent(GameObject* _owner)
	:Component(_owner)
	, animationClip(nullptr)
	, nextAnimationClip(nullptr)
{
}

AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::Update(float _deltaTime)
{
	if (animationClip == nullptr)
	{
		return;
	}
	else
	{
		animationClip->Update(_deltaTime);
		nextAnimationClip = animationClip->ChangeAnimation();
	}

	const bool changeAnimation = animationClip != nextAnimationClip;
	if (changeAnimation)
	{
		delete animationClip;
		animationClip = nextAnimationClip;
		nextAnimationClip = nullptr;
	}
}
