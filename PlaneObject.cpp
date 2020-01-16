#include "PlaneObject.h"
#include "Game.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "Mesh.h"

PlaneObject::PlaneObject()
    :GameObject()
{
    SetScale(10.0f);
	MeshComponent* mc = new MeshComponent(this);
    mc->SetMesh(RENDERER->GetMesh("Assets/Plane.gpmesh"));
}

