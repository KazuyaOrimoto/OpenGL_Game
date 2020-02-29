//=============================================================================
//	@file	SpriteComponent.cpp
//	@brief	スプライトを描画するためのコンポーネント
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

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
SpriteComponent::SpriteComponent(GameObject * _owner, int _drawOrder)
    :Component(_owner)
    ,texture(nullptr)
    ,drawOrder(_drawOrder)
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
void SpriteComponent::Draw(Shader * _shader)
{
	if (texture)
	{
		Matrix4 scaleMatrix = Matrix4::CreateScale(
			static_cast<float>(textureWidth),
			static_cast<float>(textureHeight),
			1.0f);

		Matrix4 world = scaleMatrix * owner->GetWorldTransform();

		_shader->SetMatrixUniform("uWorldTransform",world);
		
		texture->SetActive();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		
	}
}

/**
@brief	使用するテクスチャの設定
@param	使用するテクスチャのポインタ
*/
void SpriteComponent::SetTexture(Texture * _texture)
{
	texture = _texture;
	textureWidth = texture->GetWidth();
	textureHeight = texture->GetHeight();
}
