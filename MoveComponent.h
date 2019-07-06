#pragma once
#include "Component.h"

class GameObject;

class MoveComponent : public Component
{
public:
	MoveComponent(GameObject* owner, int updateOrder = 10);
	void Update(float deltaTime) override;
	void ProcessInput(const struct InputState& state) override;

	int GetForwardKey() const { return mForwardKey; }
	int GetBackKey() const { return mBackKey; }
	int GetRightKey() const { return rightKey; }
	int GetLeftKey() const { return leftKey; }
	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackKey(int key) { mBackKey = key; }
	void SetRightKey(int key) { rightKey = key; }
	void SetLeftKey(int key) { leftKey = key; }
	void SetMaxForwardSpeed(float value) { maxForwardSpeed = value; }
	void SetMaxStrafeSpeed(float value) { maxStrafeSpeed = value; }

	float GetForwardSpeed() const { return forwardSpeed; }
	float GetStrafeSpeed() const { return starafeSpeed; }
private:
	float forwardSpeed;
	float starafeSpeed;

	float maxForwardSpeed;
	float maxStrafeSpeed;

	// Keys for forward/back movement
	int mForwardKey;
	int mBackKey;
	int rightKey;
	int leftKey;
};

