#include "SlidingObject.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Collision.h"
#include "Renderer.h"
#include "ObstacleManager.h"
#include "PlayerObject.h"
#include "RotateComponent.h"
#include "Mesh.h"
#include "GameObjectManager.h"

SlidingObject::SlidingObject()
	: ObstacleBox()
	, player(nullptr)
{
	meshComp = new MeshComponent(this);
	Mesh* mesh = RENDERER->GetMesh("Assets/Cube.gpmesh");
	meshComp->SetMesh(mesh);
	boxCollider = new BoxCollider(this, GetOnCollisionFunc());
	AABB box = { Vector3::Zero , Vector3::Zero };
	std::vector<Vector3> verts = mesh->GetVerts();
	for (auto itr : verts)
	{
		box.UpdateMinMax(itr);
	}
	boxCollider->SetObjectBox(box);
	SetScale(200.0f);
	OBSTACLE_MANAGER->AddObstacle(this);

	tag = Tag::Obstacle;

	state = Paused;
	player = GAME_OBJECT_MANAGER->FindGameObject(Tag::Player);
}

SlidingObject::~SlidingObject()
{
	OBSTACLE_MANAGER->RemoveObstacle(this);
}

void SlidingObject::UpdateGameObject(float _deltaTime)
{
	if (player->GetPosition().x - 500.0f > position.x)
	{
		ResetObstacle();
	}
}

void SlidingObject::OnCollision(const GameObject& _hitObject)
{
	if (_hitObject.GetTag() == Tag::Player)
	{
		//障害物と当たった時の処理
	}
}

