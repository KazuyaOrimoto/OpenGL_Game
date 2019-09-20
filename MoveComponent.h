#pragma once
#include "Component.h"

class GameObject;
class PlayerObject;

class MoveComponent : public Component
{
public:
	MoveComponent(GameObject* _owner, int _updateOrder = 10);
	void Update(float _deltaTime) override;
	void ProcessInput(const struct InputState& _state) override;

	int GetForwardKey() const { return mForwardKey; }
	int GetBackKey() const { return mBackKey; }
	int GetRightKey() const { return rightKey; }
	int GetLeftKey() const { return leftKey; }
	void SetForwardKey(int _key) { mForwardKey = _key; }
	void SetBackKey(int _key) { mBackKey = _key; }
	void SetRightKey(int _key) { rightKey = _key; }
	void SetLeftKey(int _key) { leftKey = _key; }
	void SetMaxForwardSpeed(float _value) { maxForwardSpeed = _value; }
	void SetMaxStrafeSpeed(float _value) { maxStrafeSpeed = _value; }

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

    PlayerObject* player;
};

