#pragma once

#include "GameObject.h"

class CameraObject : public GameObject
{
public:
    CameraObject(Game* game);

    void UpdateGameObject(float deltaTime) override;
private:
};

