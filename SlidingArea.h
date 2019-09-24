#pragma once

#include "GameObject.h"

class BoxCollider;

class SlidingArea : public GameObject
{
public:
	SlidingArea(Game* _game);
	~SlidingArea();


private:
	BoxCollider* boxCollider;
};

