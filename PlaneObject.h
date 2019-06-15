#pragma once
#include "GameObject.h"

class Game;

class PlaneObject :
    public GameObject
{
public:
    PlaneObject(Game* game);
};

