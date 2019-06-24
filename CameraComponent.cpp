#include "CameraComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "GameObject.h"


CameraComponent::CameraComponent(GameObject* argOwner, int argUpdateOrder)
	:Component(argOwner,argUpdateOrder)
{
}

void CameraComponent::SetViewMatrix(const Matrix4 & view)
{
	Game* game = owner->GetGame();
	game->GetRenderer()->SetViewMatrix(view);
}


