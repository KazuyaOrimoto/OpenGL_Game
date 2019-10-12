#include "MainCamera.h"
#include "GameObject.h"
#include "SDL.h"
#include "RotateComponent.h"
#include "PlayerObject.h"

MainCamera::MainCamera(GameObject* _owner)
	:CameraComponent(_owner)
	, horzDist(1000.0f)
	, vertDist(400.0f)
	, targetDist(200.0f)
	, springConstant(500.0f)
	, rotate(nullptr)
{
	rotate = (dynamic_cast<PlayerObject*>(_owner)->GetRotate());
}

void MainCamera::Update(float _deltaTime)
{
    CameraComponent::Update(_deltaTime);

    float dampening = 2.0f * Math::Sqrt(springConstant);

    Vector3 idealPos = ComputeCameraPos();

    Vector3 diff = actualPos - idealPos;

    Vector3 acel = -springConstant * diff - dampening * velocity;

    velocity += acel * _deltaTime;

    actualPos += velocity * _deltaTime;

    Vector3 target = owner->GetPosition() + rotate->GetCameraForward() * targetDist;

    Matrix4 view = Matrix4::CreateLookAt(actualPos, target, rotate->GetCameraUp());

    SetViewMatrix(view);
}

void MainCamera::SnapToIdeal()
{
    actualPos = ComputeCameraPos();

    velocity = Vector3::Zero;

    Vector3 target = owner->GetPosition() + rotate->GetCameraForward() * targetDist;

    Matrix4 view = Matrix4::CreateLookAt(actualPos, target, rotate->GetCameraUp());

    SetViewMatrix(view);
}

Vector3 MainCamera::ComputeCameraPos() const
{
    Vector3 cameraPos = owner->GetPosition();

    cameraPos -= rotate->GetCameraForward() * horzDist;

    cameraPos += rotate->GetCameraUp() * vertDist;

    return cameraPos;
}
