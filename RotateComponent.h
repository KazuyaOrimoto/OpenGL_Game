#pragma once
#include "Component.h"
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

	int GetTorque() { return torque; }
	void ResetTorque() { torque = 0; }

private:
	void AddTorque();

	bool right;
	//回転で得た力
	int  torque;
};

