#pragma once
#include "Component.h"

class DrilObject;

class AutoRunComponent :
    public Component
{
public:
    AutoRunComponent(GameObject* owner, int updateOrder = 10);


    void Update(float deltaTime) override;
    void SetForwardSpeed(float value) { forwardSpeed = value; }
    float GetForwardSpeed() const { return forwardSpeed; }
    void SetDrilObject(DrilObject* argDril) { dril = argDril; }

private:

    float forwardSpeed;
    DrilObject* dril;

};

