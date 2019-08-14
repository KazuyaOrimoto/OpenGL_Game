#include "WallObject.h"
#include "WallManager.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "Mesh.h"
#include "WallMeshComponent.h"

WallObject::WallObject(Game* game, int i)
	:GameObject(game)
{
	SetScale(1000.0f);
	SetPosition(Vector3(i*2000.0f, 0.0f, 0.0f));
	MeshComponent* mc = new WallMeshComponent(this);
	mc->SetMesh(RENDERER->GetMesh("Assets/Wall.gpmesh"));
	WALL_MANAGER->AddWallObject(this);
}

WallObject::~WallObject()
{
}
