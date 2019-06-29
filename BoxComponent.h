#pragma once

#include "Component.h"
#include "Collision.h"

class GameObject;

class BoxComponent : public Component
{
public:
    BoxComponent(GameObject* argOwner, int argUpdateOrder = 100);
    ~BoxComponent();

    void OnUpdateWorldTransform() override;

    void SetObjectBox(const AABB& model) { objectBox = model; }
    const AABB& GetWorldBox() const { return worldBox; }

    void SetShouldRotate(bool value) { shouldRotate = value; }
private:
    AABB objectBox;
    AABB worldBox;
    bool shouldRotate;



};

