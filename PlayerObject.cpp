#include "PlayerObject.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "FollowCamera.h"
#include "MoveComponent.h"
#include "SphereCollider.h"

PlayerObject::PlayerObject(Game* game)
	:GameObject(game)
{
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::SetVisible(bool visible)
{
    meshComp->SetVisible(visible);
}
