#pragma once
#include "Component.h"
#include <vector>

class GameObject;
class AnimationClip;

class AnimationComponent :
	public Component
{
public:
	AnimationComponent(GameObject* _owner);
	~AnimationComponent();

	/**
	@brief	�t���[�����̏���
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void Update(float _deltaTime);

	void SetAnimationClip(AnimationClip* _animationClip) { animationClip = _animationClip; }
	
	/**
	@brief	�A�j���[�V�������I�����Ă��邩
	@return	true : �I�����Ă���,false : �I�����Ă��Ȃ�
	*/
	bool AnimationEnd() { return (animationClip == nullptr); }

private:
	AnimationClip* animationClip;
	AnimationClip* nextAnimationClip;
};
