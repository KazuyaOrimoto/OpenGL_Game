#pragma once
#include "Component.h"
#include "Math.h"

class DrilObject;

class RotateComponent : public Component
{
public:
	RotateComponent(GameObject* argOwner, int argUpdateOrder = 10);

	/**
	@brief	フレーム毎の処理
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void Update(float argDeltaTime);

	/**
	@brief	入力処理
	@param	InputState構造体
	*/
	virtual void ProcessInput(const struct InputState& state);

    bool CanMove() { return canMove; }
	Vector3 GetCameraUp() const { return Vector3::Transform(Vector3::UnitZ, cameraQuat); }
	Vector3 GetCameraForward() const { return Vector3::Transform(Vector3::UnitX, cameraQuat); }
private:

	void MoveWall();
	void HitRightWall();
	void HitLeftWall();
	void HitTopWall();
	void HitUnderWall();

	bool right;
    Quaternion target;
    float f;
	float moveTorque;
    bool canMove;
    Quaternion rot;
	Quaternion cameraQuat;
	Quaternion moveRot;
	Vector3 ownerPos;
};

