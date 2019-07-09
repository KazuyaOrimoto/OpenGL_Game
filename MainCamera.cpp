#include "MainCamera.h"
#include "GameObject.h"
#include "SDL.h"

MainCamera::MainCamera(GameObject* owner)
    :CameraComponent(owner)
    , horzDist(700.0f)
    , vertDist(150.0f)
    , targetDist(100.0f)
    , springConstant(750.0f)
{
}

void MainCamera::Update(float deltaTime)
{
    CameraComponent::Update(deltaTime);

    float dampening = 2.0f * Math::Sqrt(springConstant);

    Vector3 idealPos = ComputeCameraPos();

    Vector3 diff = actualPos - idealPos;

    Vector3 acel = -springConstant * diff - dampening * velocity;

    velocity += acel * deltaTime;

    actualPos += velocity * deltaTime;

    Vector3 target = owner->GetPosition() + owner->GetForward() * targetDist;

    Matrix4 view = Matrix4::CreateLookAt(actualPos, target, owner->GetUp());

    SetViewMatrix(view);
}

void MainCamera::SnapToIdeal()
{
    actualPos = ComputeCameraPos();

    velocity = Vector3::Zero;

    Vector3 target = owner->GetPosition() + owner->GetForward() * targetDist;

    Matrix4 view = Matrix4::CreateLookAt(actualPos, target, owner->GetUp());

    SetViewMatrix(view);
}

Vector3 MainCamera::ComputeCameraPos() const
{
    Vector3 cameraPos = owner->GetPosition();

    cameraPos -= owner->GetForward() * horzDist;

    cameraPos += owner->GetUp() * vertDist;

    return cameraPos;
}
