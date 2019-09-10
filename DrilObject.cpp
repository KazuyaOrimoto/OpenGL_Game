#include "DrilObject.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "SphereCollider.h"
#include "ObstacleBox.h"
#include "InputSystem.h"

DrilObject::DrilObject(Game* _game, PlayerObject* _ownerObject)
    : GameObject(_game)
    , ownerObject(_ownerObject)
{
    meshComp = new MeshComponent(this);
    meshComp->SetMesh(RENDERER->GetMesh("Assets/Bike.gpmesh"));
    SetScale(7.0f);

    sphereCollider = new SphereCollider(this);
    sphereCollider->SetObjectSphere(Sphere(Vector3(0.0f, 0.0f, 0.0f), 1.0f));

	tag = Tag::Player;
}

DrilObject::~DrilObject()
{
}

void DrilObject::UpdateGameObject(float _deltaTime)
{
	//SetRotation(ownerObject->GetRotation());
}

void DrilObject::OnCollision(GameObject & _hitObject)
{
    if (_hitObject.GetTag() == Tag::Obstacle)
    {
        //áŠQ•¨‚Æ“–‚½‚Á‚½‚Ìˆ—
        ObstacleBox* obstacle = dynamic_cast<ObstacleBox*>(&_hitObject);
        HitObstacle(*obstacle);
    }
}

void DrilObject::HitObstacle(const ObstacleBox & _hitObstacle)
{
}

void DrilObject::GameObjectInput(const InputState & _state)
{
    if (_state.Keyboard.GetKeyState(SDL_SCANCODE_D))
    {
        Quaternion rot = ownerObject->GetRotation();
        float rad = Math::ToRadians(-10);
        Quaternion inc(Vector3::UnitX, rad);
        rot = Quaternion::Concatenate(rot, inc);
        SetRotation(rot);
    }
    else if (_state.Keyboard.GetKeyState(SDL_SCANCODE_A))
    {
        Quaternion rot = ownerObject->GetRotation();
        float rad = Math::ToRadians(10);
        Quaternion inc(Vector3::UnitX, rad);
        rot = Quaternion::Concatenate(rot, inc);
        SetRotation(rot);
    }
    else
    {
        SetRotation(ownerObject->GetRotation());
    }
}

