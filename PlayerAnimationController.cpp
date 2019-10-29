#include "PlayerAnimationController.h"
#include "AnimationComponent.h"
#include "JumpAnimation.h"

PlayerAnimationController::PlayerAnimationController(GameObject* _owner, AnimationComponent* _animationComp)
	:AnimationController(_owner,_animationComp)
{
}

PlayerAnimationController::~PlayerAnimationController()
{
}

void PlayerAnimationController::Jump()
{
	JumpAnimation* jump = new JumpAnimation(owner);
	animationComp->SetAnimationClip(jump);
}
