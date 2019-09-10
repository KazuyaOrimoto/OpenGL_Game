#pragma once
#include "CameraComponent.h"

class RotateComponent;
class MainCamera : public CameraComponent
{
public:
    MainCamera(GameObject* _owner);

    void Update(float _deltaTime) override;

    void SnapToIdeal();

    void SetHorzDist(float _dist) { horzDist = _dist; }
    void SetVertDist(float _dist) { vertDist = _dist; }
    void SetTargetDist(float _dist) { targetDist = _dist; }
    void SetSpringConstant(float _spring) { springConstant = _spring; }

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

