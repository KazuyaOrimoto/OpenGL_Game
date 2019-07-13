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

private:

	bool right;
};

