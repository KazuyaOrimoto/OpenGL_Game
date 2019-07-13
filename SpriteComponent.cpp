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
    ,textureWidth(0)
    ,textureHeight(0)
{
	RENDERER->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	RENDERER->RemoveSprite(this);
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

		Matrix4 world = scaleMatrix * owner->GetWorldTransform();

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
	textureWidth = texture->GetWidth();
	textureHeight = texture->GetHeight();
}
