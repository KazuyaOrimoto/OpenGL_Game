#pragma once

#include "GameObject.h"

class BoxCollider;

class SlidingArea : public GameObject
{
public:
	SlidingArea();
	~SlidingArea();


private:
	BoxCollider* boxCollider;
};

