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
	, springConstant(300.0f)
{
	radsave = 0;
}


TitleCamera::~TitleCamera()
{
}

void TitleCamera::Update(float _deltaTime)
{
	CameraComponent::Update(_deltaTime);

	Vector3 cameraPos = Vector3::Zero;

	radsave += 3;

	cameraPos += owner->GetForward() * 300;
	cameraPos += owner->GetRight() * 400;
	cameraPos += owner->GetUp() * 150;

	//Vector3 target = Vector3::Zero;
	//target += owner->GetForward() * -300;
	//target += owner->GetRight() * -500;
	//target += owner->GetUp() * 100;

	Vector3 n = owner->GetUp();
	Vector3 r = cameraPos;
	float rad = Math::ToRadians(radsave);

	Vector3 r2 = n * (n * r) + (r - n * (n * r)) * Math::Cos(rad) - (r * n) * Math::Sin(rad);

	cameraPos = r2;

	Matrix4 view = Matrix4::CreateLookAt(r2, owner->GetPosition(), owner->GetUp());

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
	cameraPos += owner->GetRight() * 500;

	return cameraPos;
}
