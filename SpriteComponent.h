#pragma once

#include "Component.h"
#include "Property.h"

class GameObject;
class Shader;
class Texture;

class SpriteComponent : public Component
{
public:
    SpriteComponent(GameObject* argOwner, int argDrawOrder = 100);
    ~SpriteComponent();

    virtual void Draw(class Shader* shader);
    virtual void SetTexture(class Texture* argTexture);

    int GetTexWidth() const { return textureWidth; }
    int GetTexHeight() const { return textureHeight; }

	cpp_module::ReadOnlyProperty<int> readOnlyDrawOrder;
	cpp_module::ReadOnlyProperty<int> readOnlyTextureWidth;
	cpp_module::ReadOnlyProperty<int> readOnlyTextureHeight;
protected:
    Texture* texture;
    int drawOrder;
    int textureWidth;
    int textureHeight;
};

