#include "PlayerAnimationController.h"
#include "AnimationComponent.h"
#include "JumpAnimation.h"
#include "BikeObject.h"

PlayerAnimationController::PlayerAnimationController(GameObject* _owner, AnimationComponent* _animationComp)
	:AnimationController(_owner,_animationComp)
{
	bike = static_cast<BikeObject*>(_owner);
}

PlayerAnimationController::~PlayerAnimationController()
{
}

void PlayerAnimationController::Jump()
{
	JumpAnimation* jump = new JumpAnimation(owner, bike->GetCamera());
	animationComp->SetAnimationClip(jump);
}
