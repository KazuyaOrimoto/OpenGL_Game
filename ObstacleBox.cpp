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


ObstacleBox::ObstacleBox(Game* game)
	:GameObject(game)
	, hardness(1)
	, player(nullptr)
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
	OBSTACLE_MANAGER->AddOnstacle(this);

	tag = "Obstacle";

	state = Paused;
	player = GAME_OBJECT_MANAGER->FindGameObject("Player");
}


ObstacleBox::~ObstacleBox()
{
	OBSTACLE_MANAGER->RemoveObstacle(this);
}

void ObstacleBox::OnCollision(GameObject & argHitObject)
{
	if (argHitObject.GetTag() == "Player")
	{
		//áŠQ•¨‚Æ“–‚½‚Á‚½‚Ìˆ—
		PlayerObject* obstacle = dynamic_cast<PlayerObject*>(&argHitObject);
		HitPlayer(*obstacle);
	}
}

void ObstacleBox::HitPlayer(const PlayerObject & argPlayerObject)
{
	meshComp->SetVisible(false);
	ResetObstacle();
}

void ObstacleBox::ResetObstacle()
{
	SetPosition(Vector3::Zero);
	state = Paused;
}

void ObstacleBox::UseObstacle()
{
	meshComp->SetVisible(true);
	state = Active;
	GAME_OBJECT_MANAGER->RemoveGameObject(this);
	GAME_OBJECT_MANAGER->AddGameObject(this);
}

void ObstacleBox::UpdateGameObject(float argDaltaTime)
{
	if (player->GetPosition().x - 500.0f > position.x)
	{
		ResetObstacle();
	}
}
