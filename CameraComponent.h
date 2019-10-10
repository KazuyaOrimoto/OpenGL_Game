#pragma once

#include "Component.h"
#include "Math.h"

class GameObject;

class CameraComponent : public Component
{
public:
	CameraComponent(GameObject* _owner,int _updateOrder = 200);
	void Update(float _deltaTime) override;
protected:
	
	void SetViewMatrix(const Matrix4& _view);
};


