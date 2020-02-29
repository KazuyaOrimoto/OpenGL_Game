//=============================================================================
//	@file	CameraObject.h
//	@brief	カメラのオブジェクト
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#pragma once

#include "GameObject.h"

struct InputState;
class InputComponent;

class CameraObject : public GameObject
{
public:
    CameraObject();

    void UpdateGameObject(float _deltaTime) override;
private:
	InputComponent* inputComponent;
};

