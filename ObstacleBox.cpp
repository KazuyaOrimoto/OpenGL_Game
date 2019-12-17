#include "ObstacleBox.h"
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
#include <stdlib.h>
#include "SDL.h"

ObstacleBox::ObstacleBox()
	:GameObject()
	, player(nullptr)
{
	meshComp = new MeshComponent(this);

	Mesh* mesh = nullptr;
	mesh = RENDERER->GetMesh("Assets/cube.gpmesh");
	//switch ()
	//{
	//case Box:
	//	mesh = RENDERER->GetMesh("Assets/cube.gpmesh");
	//	break;
	//case Wall:
	//	mesh = RENDERER->GetMesh("Assets/ObstacleWall.gpmesh");
	//	break;
	//default:
	//	break;
	//}

	meshComp->SetMesh(mesh);
	boxCollider = new BoxCollider(this, GetOnCollisionFunc());
	AABB box = { Vector3::Zero , Vector3::Zero };
	std::vector<Vector3> verts = mesh->GetVerts();
	for (auto itr : verts)
	{
		box.UpdateMinMax(itr);
	}
	boxCollider->SetObjectBox(box);
	SetScale(100.0f);
	OBSTACLE_MANAGER->AddObstacle(this);

	tag = Tag::Obstacle;

	state = Paused;
	player = GameObject::FindGameObject(Tag::Player);
}

ObstacleBox::~ObstacleBox()
{
	OBSTACLE_MANAGER->RemoveObstacle(this);
}

void ObstacleBox::OnCollision(const GameObject& _hitObject)
{
	if (_hitObject.GetTag() == Tag::Player)
	{
		//障害物と当たった時の処理
		meshComp->SetVisible(false);
		ResetObstacle();
	}
}

void ObstacleBox::ResetObstacle()
{
	SetPosition(Vector3::Zero);
	state = Paused;
	boxCollider->CollisionPause();
	meshComp->SetVisible(false);
}

void ObstacleBox::UseObstacle()
{
	meshComp->SetVisible(true);
	state = Active;
	boxCollider->CollisionActive();
	GameObject::RemoveGameObject(this);
	GameObject::AddGameObject(this);
}

void ObstacleBox::UpdateGameObject(float _deltaTime)
{
	if (player == nullptr)
	{
		return;
	}
	if (player->GetPosition().x - 500.0f > position.x)
	{
		ResetObstacle();
	}
}
