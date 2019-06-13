#include "SpriteComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "GameObject.h"
#include "Game.h"


SpriteComponent::SpriteComponent(GameObject * argOwner, int argDrawOrder)
    :Component(argOwner)
    ,texture(nullptr)
    ,drawOrder(argDrawOrder)
	,readOnlyDrawOrder(drawOrder)
    ,textureWidth(0)
	,readOnlyTextureWidth(textureWidth)
    ,textureHeight(0)
	,readOnlyTextureHeight(textureHeight)
{
	owner->readOnlyGame->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	owner->readOnlyGame->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader * shader)
{
	if (texture)
	{
		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(textureWidth),
			static_cast<float>(textureHeight),
			1.0f);

		Matrix4 world = scaleMatrix * owner->readOnlyWorldTransform;

		shader->SetMatrixUniform("WorldTransform",world);
		
		texture->SetActive();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		
	}
}

void SpriteComponent::SetTexture(Texture * argTexture)
{
	texture = argTexture;
	textureWidth = texture->readOnlyWidth;
	textureHeight = texture->readOnlyHeight;
}
