#pragma once
class AnimationComponent;
class GameObject;
class AnimationController
{
public:
	AnimationController(GameObject* _owner, AnimationComponent* _animationComp);
	~AnimationController();

protected:
	AnimationComponent* animationComp;
	GameObject* owner;
};

