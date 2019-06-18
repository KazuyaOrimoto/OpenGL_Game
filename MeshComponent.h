#pragma once

#include "Component.h"

class GameObject;

class MeshComponent : public Component
{
public:
    MeshComponent(GameObject* owner);
    ~MeshComponent();
    virtual void Draw(class Shader* shader);
    // Set the argMesh/texture index used by argMesh component
    virtual void SetMesh(class Mesh* argMesh) { mMesh = argMesh; }
    void SetTextureIndex(size_t index) { mTextureIndex = index; }
protected:
    class Mesh* mMesh;
    size_t mTextureIndex;
};

