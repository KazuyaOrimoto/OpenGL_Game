#include "SpriteComponent.h"
#include "Texture.h"
#include "Shader.h"
#include "GameObject.h"
#include "Game.h"
#include "Renderer.h"

/**
@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
@param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
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
@brief	�`�揈��
@param	�g�p����V�F�[�_�[�N���X�̃|�C���^
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
@brief	�g�p����e�N�X�`���̐ݒ�
@param	�g�p����e�N�X�`���̃|�C���^
*/
void SpriteComponent::SetTexture(Texture * argTexture)
{
	texture = argTexture;
	textureWidth = texture->readOnlyWidth;
	textureHeight = texture->readOnlyHeight;
}
