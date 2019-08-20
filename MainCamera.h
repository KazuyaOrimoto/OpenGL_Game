#pragma once
#include "CameraComponent.h"

class RotateComponent;
class MainCamera : public CameraComponent
{
public:
    MainCamera(GameObject* owner);

    void Update(float deltaTime) override;

    void SnapToIdeal();

    void SetHorzDist(float dist) { horzDist = dist; }
    void SetVertDist(float dist) { vertDist = dist; }
    void SetTargetDist(float dist) { targetDist = dist; }
    void SetSpringConstant(float spring) { springConstant = spring; }

private:
    Vector3 ComputeCameraPos() const;

    Vector3 actualPos;

    Vector3 velocity;

    float horzDist;

    float vertDist;

    float targetDist;

    float springConstant;

	RotateComponent* rotate;
};

