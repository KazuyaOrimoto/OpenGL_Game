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

