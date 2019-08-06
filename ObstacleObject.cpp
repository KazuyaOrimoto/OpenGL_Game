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
	, hardness(0)
{
	meshComp = new MeshComponent(this);
	Mesh* mesh = RENDERER->GetMesh("Assets/Obstacle.gpmesh");
	meshComp->SetMesh(mesh);
	boxCollider = new BoxCollider(this);
	AABB box = { Vector3::Zero , Vector3::Zero };
	std::vector<Vector3> verts = mesh->GetVerts();
	for (auto itr : verts)
	{
		box.UpdateMinMax(itr);
	}
	boxCollider->SetObjectBox(box);
	SetScale(200.0f);
	SetPosition(Vector3(10000.0f, 0.0f, 1000.0f));
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
		//障害物と当たった時の処理
		PlayerObject* obstacle = dynamic_cast<PlayerObject*>(&argHitObject);
		HitPlayer(*obstacle);
	}
}

void ObstacleObject::HitPlayer(const PlayerObject & argPlayerObject)
{
	//プレイヤーの方が強かったら
	if (argPlayerObject.GetRotate()->GetTorque() > hardness)
	{


	}
	//自分の方が強かったら
	else
	{


	}


}
