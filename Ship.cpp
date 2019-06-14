#include "Ship.h"
#include "Game.h"
#include "SpriteComponent.h"


Ship::Ship(Game* game)
	:GameObject(game)
{
	SpriteComponent* sprite = new SpriteComponent(this,100);
	sprite->SetTexture(game->GetTexture("Assets/Ship.png"));
}


Ship::~Ship()
{
}

void Ship::UpdateGameObject(float argDeltaTime)
{
	position.x++;
}
