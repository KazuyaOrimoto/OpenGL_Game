#include "AnimationController.h"
#include "AnimationComponent.h"


AnimationController::AnimationController(GameObject* _owner, AnimationComponent* _animationComp)
	:animationComp(_animationComp)
	,owner(_owner)
{
}

AnimationController::~AnimationController()
{
}
