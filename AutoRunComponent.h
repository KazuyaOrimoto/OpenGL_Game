#pragma once
#include "Component.h"

class BikeObject;

class AutoRunComponent :
    public Component
{
public:
    AutoRunComponent(GameObject* _owner, int _updateOrder = 10);


    void Update(float _deltaTime) override;
    void SetForwardSpeed(float _value) { forwardSpeed = _value; }
    float GetForwardSpeed() const { return forwardSpeed; }
    void SetDrilObject(BikeObject* _dril) { dril = _dril; }

private:

    float forwardSpeed;
	BikeObject* dril;

};

