#include "PlaneObject.h"
#include "Game.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "Mesh.h"


PlaneObject::PlaneObject(Game* game)
    :GameObject(game)
{
    SetScale(10.0f);
    MeshComponent* mc = new MeshComponent(this);
    mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Plane.gpmesh"));
}

