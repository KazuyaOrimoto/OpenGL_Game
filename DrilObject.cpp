#include "DrilObject.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "SphereCollider.h"
#include "ObstacleBox.h"

DrilObject::DrilObject(Game* game, PlayerObject* argOwnerObject)
    : GameObject(game)
    , ownerObject(argOwnerObject)
{
    meshComp = new MeshComponent(this);
    meshComp->SetMesh(RENDERER->GetMesh("Assets/Bike.gpmesh"));
    SetScale(5.0f);

    sphereCollider = new SphereCollider(this);
    sphereCollider->SetObjectSphere(Sphere(Vector3(0.0f, 0.0f, 0.0f), 1.0f));

	tag = "Player";
}

DrilObject::~DrilObject()
{
}

void DrilObject::UpdateGameObject(float argDeltaTime)
{
	SetRotation(ownerObject->GetRotation());
}

void DrilObject::OnCollision(GameObject & argHitObject)
{
    if (argHitObject.GetTag() == "Obstacle")
    {
        //è·äQï®Ç∆ìñÇΩÇ¡ÇΩéûÇÃèàóù
        ObstacleBox* obstacle = dynamic_cast<ObstacleBox*>(&argHitObject);
        HitObstacle(*obstacle);
    }
}

void DrilObject::HitObstacle(const ObstacleBox & argHitObstacle)
{
}
