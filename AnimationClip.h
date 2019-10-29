#pragma once

class GameObject;

class AnimationClip
{
public:
	AnimationClip(GameObject* _gameObject, int _animationChangeCount);
	virtual ~AnimationClip();

	virtual void Update(float deltaTime) = 0;

	AnimationClip * ChangeAnimation();
	void SetNextAnimation(AnimationClip* _nextAnimation) { nextAnimation = _nextAnimation; }
protected:
	GameObject* owner;
	
	int animationCount;
	const int animationChangeCount;

private:
	AnimationClip* nextAnimation;
};

