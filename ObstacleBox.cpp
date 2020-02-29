//=============================================================================
//	@file	ObstacleBox.cpp
//	@brief	障害物のボックスのオブジェクト
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

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
#include <stdlib.h>
#include "SDL.h"
#include "HDRMeshComponent.h"

GameObject* ObstacleBox::player = nullptr;

ObstacleBox::ObstacleBox()
	:GameObject()
{
	meshComp = new HDRMeshComponent(this);

	Mesh* mesh = nullptr;
	mesh = RENDERER->GetMesh("Assets/cube.gpmesh");

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
	meshComp->SetVisible(false);
	meshComp->SetHDRColor(Vector3(0.8f,0.8f,0.8f));

	name = "Box";
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
	boxCollider->SetActive(false);
	meshComp->SetVisible(false);
}

void ObstacleBox::UseObstacle()
{
	meshComp->SetVisible(true);
	state = Active;
	boxCollider->SetActive(true);
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
