#pragma once

#include "CameraComponent.h"

class GameObject;

class FPSCamera : public CameraComponent
{
public:
	FPSCamera(GameObject* argOwner);

	void Update(float deltaTime) override;
	void ProcessInput(const struct InputState& state) override;

	float GetPitch() const { return pitch; }
	float GetPitchSpeed() const { return pitchSpeed; }
	float GetMaxPitch() const { return maxPitchSpeed; }
	//void SetPitchSpeed(float speed) { pitchSpeed = speed; }
	void SetMaxPitch(float pitch) { maxPitchSpeed = pitch; }

	float GetAngularSpeed() const { return angularSpeed; }
	float GetMaxAngular() const { return maxAngularSpeed; }
	void SetAngularSpeed(float speed) { angularSpeed = speed; }
	void SetMaxAngular(float angular) { maxAngularSpeed = pitch; }
private:

	float angularSpeed;
	float maxAngularSpeed;
	float pitch;
	float pitchSpeed;
	float maxPitch;
	float maxPitchSpeed;
};

