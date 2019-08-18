#include "ObstacleObject.h"
#include "Game.h"
#include "Collision.h"
#include "ObstacleManager.h"
#include "ObstacleBox.h"
#include "GameObjectManager.h"

ObstacleObject::ObstacleObject(Game* game, int i)
	:GameObject(game)
	,player(nullptr)
{
	CreateObstacle(5000.0f + i * 2000.0f);
}

ObstacleObject::~ObstacleObject()
{
}

void ObstacleObject::UpdateGameObject(float argDaltaTime)
{
	if (player->GetPosition().x - 500.0f > position.x)
	{
		CreateObstacle(position.x + 20 * 2000.0f);
	}
}

void ObstacleObject::CreateObstacle(float depth)
{
	GameObject* box = OBSTACLE_MANAGER->GetObstacle();
	box->SetState(Active);
	box->SetPosition(Vector3(depth, -0.0f, 150.0f));

	box = OBSTACLE_MANAGER->GetObstacle();
	box->SetState(Active);
	box->SetPosition(Vector3(depth, -0.0f, 1850.0f));
	SetPosition(Vector3(depth, -0.0f, 0.0f));
	player = GAME_OBJECT_MANAGER->FindGameObject("Player");
}
