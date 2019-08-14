#pragma once
#include "MeshComponent.h"
class WallMeshComponent :
    public MeshComponent
{
public:
    WallMeshComponent(GameObject* owner);
    ~WallMeshComponent();
};

