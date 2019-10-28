#pragma once

class GameObject;

class AnimationClip
{
public:
	AnimationClip(AnimationClip* _nextAnimation,GameObject* _gameObject);
	~AnimationClip();

	virtual AnimationClip* Update() = 0;

private:
	GameObject* gameObject;
};

