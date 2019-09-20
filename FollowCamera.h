#pragma once

#include "CameraComponent.h"

class GameObject;

class FollowCamera : public CameraComponent
{
public:
	FollowCamera(GameObject* _owner);

	void Update(float _deltaTime) override;

	void ProcessInput(const struct InputState& _state) override;

	void SnapToIdeal();

	void SetHorzDist(float _dist) { horzDist = _dist; }
	void SetVertDist(float _dist) { vertDist = _dist; }
	void SetTargetDist(float _dist) { targetDist = _dist; }
	void SetSpringConstant(float _spring) { springConstant = _spring; }

	void SetForwardKey(int _key) { mForwardKey = _key; }
	void SetBackKey(int _key) { mBackKey = _key; }
	void SetRightKey(int _key) { rightKey = _key; }
	void SetLeftKey(int _key) { leftKey = _key; }

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
