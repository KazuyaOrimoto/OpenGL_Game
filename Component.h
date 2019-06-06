#pragma once

class GameObject;

class Component
{
public:
	Component(GameObject* argOwner,int argUpdateOrder = 100);
	virtual ~Component();

	virtual void Update(float argDeltaTime);

	int GetUpdateOrder() const { return updateOrder; }

private:
	GameObject* owner;
	int updateOrder;

};

