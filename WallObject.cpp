#include "WallObject.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "Mesh.h"
#include "GameObjectManager.h"
#include "BoxCollider.h"

bool WallObject::gameEnd = false;
GameObject* WallObject::player = nullptr;

WallObject::WallObject(int _i)
	:GameObject()
{
	SetScale(1000.0f);
	SetPosition(Vector3(_i*2000.0f, 0.0f, 1000.0f));
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(RENDERER->GetMesh("Assets/Wall.gpmesh"));
	player = GameObject::FindGameObject(Tag::Player);
	tag = Tag::Wall;

	name = "Wall";
	gameEnd = false;
}

WallObject::~WallObject()
{
}

void WallObject::UpdateGameObject(float _deltaTime)
{
	//ゲーム終了フラグが立っていたら壁の更新をやめる
	if (gameEnd)
	{
		bool moveRequired = player->GetPosition().x - 2000.0f > position.x;
		if (moveRequired)
		{
			delete this;
		}
		return;
	}
	if (player == nullptr)
	{
		return;
	}
	bool moveRequired = player->GetPosition().x - 2000.0f > position.x;
	if (moveRequired)
	{
		SetPosition(Vector3(position.x + 2000.0f * 10,position.y,position.z));;
	}
}
