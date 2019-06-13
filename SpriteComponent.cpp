#include "SpriteComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "GameObject.h"
#include "Game.h"


SpriteComponent::SpriteComponent(GameObject * argOwner, int argDrawOrder)
    :Component(argOwner)
    ,texture(nullptr)
    ,drawOrder(argDrawOrder)
    ,textureWidth(0)
    ,textureHeight(0)
{
    owner->readOnlyGame;
}

SpriteComponent::~SpriteComponent()
{
}
