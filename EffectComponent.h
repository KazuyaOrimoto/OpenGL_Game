#pragma once
#include "Component.h"
#include <string>

class EffectComponent :
    public Component
{
public:
    EffectComponent(GameObject* _owner);
    ~EffectComponent();

    void LoadEffect(std::string _filename);
    void Stop();
    void Play();

private:
    int handle;
    Vector3 position;
};

