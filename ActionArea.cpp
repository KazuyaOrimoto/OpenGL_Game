#include "ActionArea.h"
#include "MeshComponent.h"
#include "Renderer.h"
#include "BikeObject.h"

ActionArea::ActionArea(GameObject* _owner)
	: GameObject()
{
	meshComp = new MeshComponent(this);
	meshComp->SetMesh(RENDERER->GetMesh("Assets/ActionArea.gpmesh"));

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
