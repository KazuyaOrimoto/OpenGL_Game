#include "BikeObject.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "PlayerObject.h"
#include "SphereCollider.h"
#include "ObstacleBox.h"
#include "InputSystem.h"
#include "jumpCheck.h"

BikeObject::BikeObject(PlayerObject* _ownerObject)
    : GameObject()
    , ownerObject(_ownerObject)
	, animation(false)
	, animNum(0)
{
    meshComp = new MeshComponent(this);
    meshComp->SetMesh(RENDERER->GetMesh("Assets/Bike.gpmesh"));
    SetScale(7.0f);

    sphereCollider = new SphereCollider(this, GetOnCollisionFunc());
    sphereCollider->SetObjectSphere(Sphere(Vector3(0.0f, 0.0f, 0.0f), 1.0f));

	SetPosition(ownerObject->GetPosition());

	tag = Tag::Player;
	new JumpCheck(this);
}

BikeObject::~BikeObject()
{
}

void BikeObject::UpdateGameObject(float _deltaTime)
{
	Animation();
}

void BikeObject::OnCollision(const GameObject& _hitObject)
{
    if (_hitObject.GetTag() == Tag::Obstacle)
    {
        //áŠQ•¨‚Æ“–‚½‚Á‚½Žž‚Ìˆ—
		animation = true;
		meshComp->SetVisible(false);
    }
}

void BikeObject::GameObjectInput(const InputState & _state)
{
	if (_state.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) && _state.Keyboard.GetKeyState(SDL_SCANCODE_LEFT))
	{
		SetRotation(ownerObject->GetRotation());
	}
    else if (_state.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT))
    {
        Quaternion rot = ownerObject->GetRotation();
        float rad = Math::ToRadians(-10);
        Quaternion inc(Vector3::UnitX, rad);
        rot = Quaternion::Concatenate(rot, inc);
        SetRotation(rot);
    }
    else if (_state.Keyboard.GetKeyState(SDL_SCANCODE_LEFT))
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

void BikeObject::Animation()
{
	if (animation)
	{
		animNum++;
		if (animNum > 20)
		{
			meshComp->SetVisible(true);
		}
		if (animNum > 20 * 2)
		{
			meshComp->SetVisible(false);
		}
		if (animNum > 20 * 3)
		{
			animation = false;
			meshComp->SetVisible(true);
			animNum = 0;
		}
	}
}

