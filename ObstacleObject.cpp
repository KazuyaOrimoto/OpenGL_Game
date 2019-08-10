#include "ObstacleObject.h"
#include "BoxCollider.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Collision.h"
#include "Renderer.h"
#include "ObstacleManager.h"
#include "PlayerObject.h"
#include "RotateComponent.h"
#include "Mesh.h"

ObstacleObject::ObstacleObject(Game* game)
	:GameObject(game)
	, hardness(1)
{
	meshComp = new MeshComponent(this);
	Mesh* mesh = RENDERER->GetMesh("Assets/Cube.gpmesh");
	meshComp->SetMesh(mesh);
	boxCollider = new BoxCollider(this);
	AABB box = { Vector3::Zero , Vector3::Zero };
	std::vector<Vector3> verts = mesh->GetVerts();
	for (auto itr : verts)
	{
		box.UpdateMinMax(itr);
	}
	boxCollider->SetObjectBox(box);
	SetScale(300.0f);
	SetPosition(Vector3(5000.0f, -800.0f, 150.0f));
	OBSTACLE_MANAGER->AddOnstacle(this);

	tag = "Obstacle";
}

ObstacleObject::~ObstacleObject()
{
}

void ObstacleObject::OnCollision(GameObject & argHitObject)
{
	if (argHitObject.GetTag() == "Player")
	{
		//áŠQ•¨‚Æ“–‚½‚Á‚½‚Ìˆ—
		PlayerObject* obstacle = dynamic_cast<PlayerObject*>(&argHitObject);
		HitPlayer(*obstacle);
	}
}

void ObstacleObject::HitPlayer(const PlayerObject & argPlayerObject)
{
	//ƒvƒŒƒCƒ„[‚Ì•û‚ª‹­‚©‚Á‚½‚ç
	if (argPlayerObject.GetRotate()->GetTorque() > hardness)
	{
		meshComp->SetVisible(false);
		SetState(Paused);
	}
	//©•ª‚Ì•û‚ª‹­‚©‚Á‚½‚ç
	else
	{


	}
}
