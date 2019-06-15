#include "SpriteComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"

/**
@param	アタッチするゲームオブジェクトのポインタ
@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
*/
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
    owner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    owner->GetGame()->GetRenderer()->RemoveSprite(this);
}

/**
@brief	描画処理
@param	使用するシェーダークラスのポインタ
*/
void SpriteComponent::Draw(Shader * shader)
{
	if (texture)
	{
		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(textureWidth),
			static_cast<float>(textureHeight),
			1.0f);

		Matrix4 world = scaleMatrix * owner->readOnlyWorldTransform;

		shader->SetMatrixUniform("uWorldTransform",world);
		
		texture->SetActive();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		
	}
}

/**
@brief	使用するテクスチャの設定
@param	使用するテクスチャのポインタ
*/
void SpriteComponent::SetTexture(Texture * argTexture)
{
	texture = argTexture;
	textureWidth = texture->readOnlyWidth;
	textureHeight = texture->readOnlyHeight;
}
