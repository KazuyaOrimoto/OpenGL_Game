#pragma once

#include "Component.h"
#include "Math.h"

class GameObject;

class CameraComponent : public Component
{
public:
	CameraComponent(GameObject* argOwner,int argUpdateOrder = 200);
protected:
	
	void SetViewMatrix(const Matrix4& view);
};


