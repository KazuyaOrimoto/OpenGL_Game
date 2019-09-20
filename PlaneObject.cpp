#include "PlaneObject.h"
#include "Game.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "WallMeshComponent.h"

PlaneObject::PlaneObject(Game* _game)
    :GameObject(_game)
{
    SetScale(10.0f);
    WallMeshComponent* mc = new WallMeshComponent(this);
    mc->SetMesh(RENDERER->GetMesh("Assets/Plane.gpmesh"));
}

