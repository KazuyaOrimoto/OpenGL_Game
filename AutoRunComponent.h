#pragma once
#include "Component.h"
class AutoRunComponent :
    public Component
{
public:
    AutoRunComponent(GameObject* owner, int updateOrder = 10);


    void Update(float deltaTime) override;
    void SetForwardSpeed(float value) { forwardSpeed = value; }
    float GetForwardSpeed() const { return forwardSpeed; }

private:

    float forwardSpeed;

};

