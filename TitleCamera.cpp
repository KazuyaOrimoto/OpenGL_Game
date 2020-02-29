//=============================================================================
//	@file	TitleCamera.cpp
//	@brief	タイトル用のカメラ
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

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

	Vector3 cameraPos = owner->GetPosition();

	cameraPos += owner->GetForward() * 300;
	cameraPos += owner->GetRight() * 400;
	cameraPos += owner->GetUp() * 150;

	Vector3 target = owner->GetPosition();
	target += owner->GetForward() * -300;
	target += owner->GetRight() * -500;
	target += owner->GetUp() * 100;

	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, owner->GetUp());

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
