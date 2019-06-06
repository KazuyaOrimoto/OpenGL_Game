#include "Game.h"
#include "Math.h"
#include "Property.h"
#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(Game * argGame)
	: state(Active)
	, position(Vector2::Zero)
	, readOnlyPosition(position)
	, scale(1.0f)
	, rotation(0.0f)
	, game(argGame)
{
}

GameObject::~GameObject()
{
}

void GameObject::Update(float argDaltaTime)
{
	if (state == Active)
	{
		
	}
}

void GameObject::UpdateComponents(float argDaltaTime)
{
}

void GameObject::UpdateActor(float argDaltaTime)
{
}

void GameObject::AddComponent(Component * argComponent)
{
}

void GameObject::RemoveComponent(Component * argComponent)
{
}
