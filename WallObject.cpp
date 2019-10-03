#include "WallObject.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "Mesh.h"
#include "WallMeshComponent.h"
#include "GameObjectManager.h"

WallObject::WallObject(int _i)
	:GameObject()
{
	SetScale(1000.0f);
	SetPosition(Vector3(_i*2000.0f, 0.0f, 0.0f));
	MeshComponent* mc = new WallMeshComponent(this);
	mc->SetMesh(RENDERER->GetMesh("Assets/Wall.gpmesh"));
	player = GAME_OBJECT_MANAGER->FindGameObject(Tag::Player);
	tag = Tag::Wall;
}

WallObject::~WallObject()
{
}

void WallObject::UpdateGameObject(float _deltaTime)
{
	bool moveRequired = player->GetPosition().x - 2000.0f > position.x;
	if (moveRequired)
	{
		SetPosition(Vector3(position.x + 2000.0f * 20,position.y,position.z));;
	}
}
