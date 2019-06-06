#pragma once
#include <vector>
#include "Math.h"
#include "Property.h"

class Game;
class Vector2;
class Component;

class GameObject
{
public:
	enum State
	{
		Active,
		Paused,
		Dead
	};
	/**
	@param	ゲームクラスのポインタ
	*/
	GameObject(Game* argGame);
	virtual ~GameObject();

	/**
	@param	ゲームクラスのポインタ
	*/
	void Update(float argDaltaTime);
	void UpdateComponents(float argDaltaTime);
	virtual void UpdateActor(float argDaltaTime);

	cpp_module::ReadOnlyProperty<Vector2> readOnlyPosition;

	void AddComponent(Component* argComponent);
	void RemoveComponent(Component* argComponent);

private:

	State state;

	Vector2 position;
	float scale;
	float rotation;

	std::vector<class Component*>components;
	class Game* game;

};

