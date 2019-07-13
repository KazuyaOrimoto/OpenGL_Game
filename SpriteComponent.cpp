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

		Matrix4 world = scaleMatrix * owner->GetWorldTransform();

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
	textureWidth = texture->GetWidth();
	textureHeight = texture->GetHeight();
}
