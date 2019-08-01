#include "ObstacleObject.h"
#include "BoxCollider.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Collision.h"
#include "Renderer.h"
#include "ObstacleManager.h"


ObstacleObject::ObstacleObject(Game* game)
	:GameObject(game)
{
	meshComp = new MeshComponent(this);
	meshComp->SetMesh(RENDERER->GetMesh("Assets/Obstacle.gpmesh"));
	boxCollider = new BoxCollider(this);
	boxCollider->SetObjectBox(AABB(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.5f, 0.5f, 0.5f)));
	SetScale(250.0f);
	SetPosition(Vector3(10000.0f, 0.0f, 150.0f));
    OBSTACLE_MANAGER->AddOnstacle(this);

    tag = "Obstacle";
}


ObstacleObject::~ObstacleObject()
{
}
