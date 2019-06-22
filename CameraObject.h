#pragma once

#include "GameObject.h"

struct InputState;
class InputComponent;

class CameraObject : public GameObject
{
public:
    CameraObject(Game* game);

    void UpdateGameObject(float deltaTime) override;
private:
	InputComponent* inputComponent;
};

