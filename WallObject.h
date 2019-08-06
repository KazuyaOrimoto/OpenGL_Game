#pragma once
#include "GameObject.h"
class WallObject :
	public GameObject
{
public:
	WallObject(Game* game,int i);
	~WallObject();
};

