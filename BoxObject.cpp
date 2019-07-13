#include "BoxObject.h"
#include "BoxCollider.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Collision.h"
#include "Renderer.h"

BoxObject::BoxObject(Game* game)
    :GameObject(game)
{
    meshComp = new MeshComponent(this);
    meshComp->SetMesh(game->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
    boxCollider = new BoxCollider(this);
    boxCollider->SetObjectBox(AABB(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.5f, 0.5f, 0.5f)));
    SetPosition(Vector3(2000.0f, -75.0f, 150.0f));
    SetScale(100.0f);
}


BoxObject::~BoxObject()
{
}
