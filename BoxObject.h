#pragma once
#include "GameObject.h"

class MeshComponent;
class BoxCollider;

class BoxObject : public GameObject
{
public:
    BoxObject(Game* _game);
    ~BoxObject();

private:
    MeshComponent* meshComp;
    BoxCollider* boxCollider;

};

