#include "PlayerObject.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "MoveComponent.h"
#include "SphereCollider.h"
#include "MainCamera.h"
#include "AutoRunComponent.h"

PlayerObject::PlayerObject(Game* game)
	:GameObject(game)
{
    meshComp = new MeshComponent(this);
    meshComp->SetMesh(game->GetRenderer()->GetMesh("Assets/Sphere.gpmesh"));
    SetPosition(Vector3(0.0f, -0.0f, 100.0f));
    SetScale(10.0f);

    moveComp = new MoveComponent(this);
    moveComp->SetRightKey(SDL_SCANCODE_D);
    moveComp->SetLeftKey(SDL_SCANCODE_A);
    moveComp->SetMaxStrafeSpeed(1200.0f);
    camera = new MainCamera(this);
    camera->SnapToIdeal();
    autoRun = new AutoRunComponent(this);
    autoRun->SetForwardSpeed(1200.0f);

    sphereCollider = new SphereCollider(this);
    sphereCollider->SetObjectSphere(Sphere(Vector3(0.0f, 0.0f, 0.0f), 1.0f));
}

void PlayerObject::SetVisible(bool visible)
{
    meshComp->SetVisible(visible);
}

