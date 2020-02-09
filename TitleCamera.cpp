#include "TitleCamera.h"
#include "GameObject.h"
#include "TitlePlayer.h"
#include "SDL.h"
#include "EffekseerManager.h"


TitleCamera::TitleCamera(GameObject* _owner)
	:CameraComponent(_owner)
	, horzDist(-1000.0f)
	, vertDist(300.0f)
	, targetDist(-1000.0f)
	, springConstant(500.0f)
{
}


TitleCamera::~TitleCamera()
{
}

void TitleCamera::Update(float _deltaTime)
{
	CameraComponent::Update(_deltaTime);

	float dampening = 2.0f * Math::Sqrt(springConstant);

	Vector3 idealPos = ComputeCameraPos();

	Vector3 diff = actualPos - idealPos;

	Vector3 acel = -springConstant * diff - dampening * velocity;

	velocity += acel * _deltaTime;

	actualPos += velocity * _deltaTime;

	Vector3 target = owner->GetPosition() + owner->GetForward() * targetDist;

	Matrix4 view = Matrix4::CreateLookAt(actualPos, target, owner->GetUp());

	SetViewMatrix(view);
	EFFECT_MANAGER->UpdateCameraMatrix();
}

void TitleCamera::SnapToIdeal()
{
	actualPos = ComputeCameraPos();

	velocity = Vector3::Zero;

	Vector3 target = owner->GetPosition() + owner->GetForward() * targetDist;

	Matrix4 view = Matrix4::CreateLookAt(actualPos, target, owner->GetUp());

	SetViewMatrix(view);
}

Vector3 TitleCamera::ComputeCameraPos() const
{
	Vector3 cameraPos = owner->GetPosition();

	cameraPos -= owner->GetForward() * horzDist;

	cameraPos += owner->GetUp() * vertDist;

	return cameraPos;
}
