#pragma once

#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	// Lower update order to update first
	InputComponent(class GameObject* _owner);

	void ProcessInput(const struct InputState& _state) override;

	// Getters/setters for private variables
	float GetMaxForward() const { return mMaxForwardSpeed; }
	float GetMaxAngular() const { return mMaxAngularSpeed; }
	int GetForwardKey() const { return mForwardKey; }
	int GetBackKey() const { return mBackKey; }
	int GetClockwiseKey() const { return mClockwiseKey; }
	int GetCounterClockwiseKey() const { return mCounterClockwiseKey; }

	void SetMaxForwardSpeed(float _speed) { mMaxForwardSpeed = _speed; }
	void SetMaxAngularSpeed(float _speed) { mMaxAngularSpeed = _speed; }
	void SetForwardKey(int _key) { mForwardKey = _key; }
	void SetBackKey(int _key) { mBackKey = _key; }
	void SetClockwiseKey(int _key) { mClockwiseKey = _key; }
	void SetCounterClockwiseKey(int _key) { mCounterClockwiseKey = _key; }
private:
	// The maximum forward/angular speeds
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;
	// Keys for forward/back movement
	int mForwardKey;
	int mBackKey;
	// Keys for angular movement
	int mClockwiseKey;
	int mCounterClockwiseKey;
};

