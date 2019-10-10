#pragma once

#include "CameraComponent.h"

class GameObject;

class FPSCamera : public CameraComponent
{
public:
	FPSCamera(GameObject* _owner);

	void Update(float _deltaTime) override;
	void ProcessInput(const struct InputState& _state) override;

	float GetPitch() const { return pitch; }
	float GetPitchSpeed() const { return pitchSpeed; }
	float GetMaxPitch() const { return maxPitchSpeed; }
	//void SetPitchSpeed(float speed) { pitchSpeed = speed; }
	void SetMaxPitch(float _pitch) { maxPitchSpeed = _pitch; }

	float GetAngularSpeed() const { return angularSpeed; }
	float GetMaxAngular() const { return maxAngularSpeed; }
	void SetAngularSpeed(float _speed) { angularSpeed = _speed; }
	void SetMaxAngular(float _angular) { maxAngularSpeed = pitch; }
private:

	float angularSpeed;
	float maxAngularSpeed;
	float pitch;
	float pitchSpeed;
	float maxPitch;
	float maxPitchSpeed;
};

