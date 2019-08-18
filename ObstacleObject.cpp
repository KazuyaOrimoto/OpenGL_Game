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
#include "ObstacleBox.h"

ObstacleObject::ObstacleObject(Game* game)
	:GameObject(game)
{
	GameObject* box = new ObstacleBox(game);
	box->SetPosition(Vector3(5000.0f,-0.0f,150.0f));

	box = new ObstacleBox(game);
	box->SetPosition(Vector3(5000.0f, -0.0f, 1850.0f));
}

ObstacleObject::~ObstacleObject()
{
}
