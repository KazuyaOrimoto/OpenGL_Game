#include "Obstacle1.h"
#include "Game.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "ObstacleObject.h"

Obstacle1::Obstacle1(Game* game)
	:GameObject(game)
{
    GameObject* box = new ObstacleObject(game);
    box->SetPosition(Vector3(5000.0f, -0.0f, 150.0f));

    box = new ObstacleObject(game);
    box->SetPosition(Vector3(5000.0f, -0.0f, 1850));

}


Obstacle1::~Obstacle1()
{
}
