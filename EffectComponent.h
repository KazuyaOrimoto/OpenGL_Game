#pragma once
#include "Component.h"
#include <string>
#include "Math.h"

class EffectComponent :
    public Component
{
public:
    EffectComponent(GameObject* _owner);
    ~EffectComponent();

    void LoadEffect(std::string _filename,Vector3 _position = Vector3::Zero);
    void Stop();
    void Play();

	void SetPosition(const Vector3& _pos);
	void SetRotation(const Quaternion& _rot);
	void SetSize(const Vector3& _size);

    Vector3 GetPosition() const { return position; }
    Quaternion GetRotation() const { return rotation; }
    Vector3 GetSize() const { return size; }

private:
    int handle;
    Vector3 position;
    Quaternion rotation;
    Vector3 size;
};

