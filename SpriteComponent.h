#pragma once

#include "Component.h"

class GameObject;
class Shader;
class Texture;

class SpriteComponent : public Component
{
public:
    SpriteComponent(GameObject* argOwner, int argDrawOrder = 100);
    ~SpriteComponent();

    virtual void Draw(class Shader* shader);
    virtual void SetTexture(class Texture* texture);

    int GetDrawOrder() const { return drawOrder; }
    int GetTexWidth() const { return textureWidth; }
    int GetTexHeight() const { return textureHeight; }

protected:
    Texture * texture;
    int drawOrder;
    int textureWidth;
    int textureHeight;
};

