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
	@brief	フレーム毎の処理
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void Update(float _deltaTime);

	void SetAnimationClip(AnimationClip* _animationClip) { animationClip = _animationClip; }
	
	/**
	@brief	アニメーションが終了しているか
	@return	true : 終了している,false : 終了していない
	*/
	bool AnimationEnd() { return (animationClip == nullptr); }

private:
	AnimationClip* animationClip;
	AnimationClip* nextAnimationClip;
};
