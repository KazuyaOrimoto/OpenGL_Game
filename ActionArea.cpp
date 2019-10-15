#include "ActionArea.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "BikeObject.h"

ActionArea::ActionArea(GameObject* _owner)
	: GameObject()
{
	meshComp = new MeshComponent(this);
	meshComp->SetMesh(RENDERER->GetMesh("Assets/ActionArea.gpmesh"));
	meshComp2 = new MeshComponent(this);
	meshComp2->SetMesh(RENDERER->GetMesh("Assets/ActionArea2.gpmesh"));
	meshComp2->SetVisible(false);

	SetPosition(_owner->GetPosition());
	owner = _owner;
	SetScale(200.0f);
}


ActionArea::~ActionArea()
{
}

void ActionArea::UpdateGameObject(float _deltaTime)
{
	Vector3 nextPos = owner->GetPosition();
	nextPos.x += (CHECK_AREA_MAX.x + CHECK_AREA_MIN.x) / 2;
	nextPos += (owner->GetUp() * -1.0f) * 49.0f;
	SetPosition(nextPos);

	SetRotation(owner->GetRotation());
}

void ActionArea::CanJump()
{
	meshComp->SetVisible(false);
	meshComp2->SetVisible(true);
}

void ActionArea::CanNotJump()
{
	meshComp->SetVisible(true);
	meshComp2->SetVisible(false);
}
