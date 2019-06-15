#pragma once

#include "Component.h"

class GameObject;

class MeshComponent : public Component
{
public:
    MeshComponent(GameObject* owner);
    ~MeshComponent();
    virtual void Draw(class Shader* shader);
    // Set the mesh/texture index used by mesh component
    virtual void SetMesh(class Mesh* mesh) { mMesh = mesh; }
    void SetTextureIndex(size_t index) { mTextureIndex = index; }
protected:
    class Mesh* mMesh;
    size_t mTextureIndex;
};

