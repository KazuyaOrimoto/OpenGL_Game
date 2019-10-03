#include "CameraComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "GameObject.h"


CameraComponent::CameraComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner,_updateOrder)
{
}

void CameraComponent::Update(float _deltaTime)
{
	Vector3 cameraPos = owner->GetPosition();

	Quaternion q(owner->GetRight(), 0.0f);

	Vector3 viewForward = Vector3::Transform(owner->GetForward(), q);

	Vector3 target = cameraPos + viewForward * 100.0f;

	Vector3 up = Vector3::Transform(Vector3::UnitZ, q);

	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);

	RENDERER->SetViewMatrix(view);
}

void CameraComponent::SetViewMatrix(const Matrix4 & _view)
{
	RENDERER->SetViewMatrix(_view);
}


