#include "AnimationClip.h"
#include "GameObject.h"

AnimationClip::AnimationClip(AnimationClip* _nextAnimation, GameObject* _gameObject)
	:gameObject(_gameObject)
{
}

AnimationClip::~AnimationClip()
{
}
