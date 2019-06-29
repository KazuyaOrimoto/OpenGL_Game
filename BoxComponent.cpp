#include "BoxComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "PhysicsWorld.h"

BoxComponent::BoxComponent(GameObject* argOwner, int argUpdateOrder)
    :Component(argOwner,argUpdateOrder)
    , objectBox(Vector3::Zero, Vector3::Zero)
    , worldBox(Vector3::Zero, Vector3::Zero)
    , shouldRotate(true)
{
    owner->GetGame()->GetPhysicsWorld()->AddBox(this);
}

BoxComponent::~BoxComponent()
{
    owner->GetGame()->GetPhysicsWorld()->RemoveBox(this);
}

void BoxComponent::OnUpdateWorldTransform()
{
    worldBox = objectBox;

    worldBox.min *= owner->GetScale();
    worldBox.max *= owner->GetScale();

    if (shouldRotate)
    {
        worldBox.Rotate(owner->GetRotation());

    }
    worldBox.min += owner->GetPosition();
    worldBox.max += owner->GetPosition();
}
