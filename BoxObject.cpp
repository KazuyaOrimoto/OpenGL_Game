#include "BoxObject.h"
#include "BoxCollider.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Collision.h"
#include "Renderer.h"

BoxObject::BoxObject()
    :GameObject()
{
    meshComp = new MeshComponent(this);
    meshComp->SetMesh(RENDERER->GetMesh("Assets/Obstacle.gpmesh"));
    boxCollider = new BoxCollider(this, GetOnCollisionFunc());
    boxCollider->SetObjectBox(AABB(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.5f, 0.5f, 0.5f)));
    SetPosition(Vector3(2000.0f, 900.0f, 0.0f));
    SetScale(250.0f);
}


BoxObject::~BoxObject()
{
}
