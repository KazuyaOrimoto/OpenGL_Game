#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;

class BoxObject : public GameObject
{
public:
    BoxObject();
    ~BoxObject();

private:
    MeshComponent* meshComp;
    BoxCollider* boxCollider;

};

