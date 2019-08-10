#pragma once
#include "GameObject.h"

class Game;

class Obstacle1 :
	public GameObject
{
public:
	Obstacle1(Game* game);
	~Obstacle1();
};

