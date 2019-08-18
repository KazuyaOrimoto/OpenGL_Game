#include "DrilObject.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "SphereCollider.h"
#include "ObstacleBox.h"
#include "RotateComponent.h"

DrilObject::DrilObject(Game* game, PlayerObject* argOwnerObject)
    : GameObject(game)
    , ownerObject(argOwnerObject)
{

    meshComp = new MeshComponent(this);
    meshComp->SetMesh(RENDERER->GetMesh("Assets/dril.gpmesh"));
    SetScale(10.0f);

    sphereCollider = new SphereCollider(this);
    sphereCollider->SetObjectSphere(Sphere(Vector3(0.0f, 0.0f, 0.0f), 10.0f));

}

DrilObject::~DrilObject()
{
}

void DrilObject::UpdateGameObject(float argDeltaTime)
{
    int torque = ownerObject->GetRotate()->GetTorque();

    Quaternion rot = rotation;
    Quaternion inc(Vector3::UnitX, static_cast<float>(torque * -0.01));
    rot = Quaternion::Concatenate(rot, inc);
    rotation = rot;

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
	ownerObject->GetRotate()->SubTorque();
}
