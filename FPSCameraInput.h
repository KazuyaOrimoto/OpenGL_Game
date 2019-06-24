#pragma once

#include "MoveComponent.h"
#include <cstdint>

class FPSCameraInput : public MoveComponent
{
public:
	// Lower update order to update first
	FPSCameraInput(class GameObject* owner);

	void ProcessInput(const struct InputState& state) override;

	// Getters/setters for private variables
	float GetMaxForward() const { return mMaxForwardSpeed; }
	float GetMaxAngular() const { return mMaxAngularSpeed; }
	int GetForwardKey() const { return mForwardKey; }
	int GetBackKey() const { return mBackKey; }
	int GetRightKey() const { return rightKey; }
	int GetLeftKey() const { return leftKey; }
	int GetClockwiseKey() const { return mClockwiseKey; }
	int GetCounterClockwiseKey() const { return mCounterClockwiseKey; }

	void SetMaxForwardSpeed(float speed) { mMaxForwardSpeed = speed; }
	void SetMaxAngularSpeed(float speed) { mMaxAngularSpeed = speed; }
	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackKey(int key) { mBackKey = key; }
	void SetRightKey(int key) { rightKey = key; }
	void SetLeftKey(int key) { leftKey = key; }
	void SetClockwiseKey(int key) { mClockwiseKey = key; }
	void SetCounterClockwiseKey(int key) { mCounterClockwiseKey = key; }
private:
	// The maximum forward/angular speeds
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;
	// Keys for forward/back movement
	int mForwardKey;
	int mBackKey;
	int rightKey;
	int leftKey;
	// Keys for angular movement
	int mClockwiseKey;
	int mCounterClockwiseKey;
};

