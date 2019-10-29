#include "AnimationClip.h"
#include "GameObject.h"

AnimationClip::AnimationClip(GameObject* _gameObject, int _animationChangeCount)
	: owner(_gameObject)
	, animationCount(0)
	, animationChangeCount(_animationChangeCount)
	, nextAnimation(nullptr)
{
}

AnimationClip::~AnimationClip()
{
}

AnimationClip * AnimationClip::ChangeAnimation()
{
	animationCount++;
	if (animationCount >= animationChangeCount)
	{
		return nextAnimation;
	}
	else
	{
		return this;
	}
}
