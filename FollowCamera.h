#pragma once

#include "CameraComponent.h"

class GameObject;

class FollowCamera : public CameraComponent
{
public:
	FollowCamera(GameObject* owner);

	void Update(float deltaTime) override;

	void ProcessInput(const struct InputState& state) override;

	void SnapToIdeal();

	void SetHorzDist(float dist) { horzDist = dist; }
	void SetVertDist(float dist) { vertDist = dist; }
	void SetTargetDist(float dist) { targetDist = dist; }
	void SetSpringConstant(float spring) { springConstant = spring; }

	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackKey(int key) { mBackKey = key; }
	void SetRightKey(int key) { rightKey = key; }
	void SetLeftKey(int key) { leftKey = key; }

private:
	Vector3 ComputeCameraPos() const;

	Vector3 actualPos;

	Vector3 velocity;

	float horzDist;

	float vertDist;

	float targetDist;

	float springConstant;

	float angularSpeed;
	int mForwardKey;
	int mBackKey;
	int rightKey;
	int leftKey;
};
