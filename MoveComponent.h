#pragma once
#include "Component.h"

class GameObject;

class MoveComponent : public Component
{
public:
	MoveComponent(GameObject* owner, int updateOrder = 10);
	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return angularSpeed; }
	float GetPitchSpeed() const { return pitchSpeed; }
	float GetForwardSpeed() const { return forwardSpeed; }
	float GetStrafeSpeed() const { return strafeSpeed; }
	void SetAngularSpeed(float speed) { angularSpeed = speed; }
	void SetPitchSpeed(float speed) { pitchSpeed = speed; }
	void SetForwardSpeed(float speed) { forwardSpeed = speed; }
	void SetStrafeSpeed(float speed) { strafeSpeed = speed; }
private:
	float angularSpeed;
	float pitchSpeed;
	float pitch;
	float maxPitch;
	float forwardSpeed;
	float strafeSpeed;
};

