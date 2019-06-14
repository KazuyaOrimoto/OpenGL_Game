#pragma once

#include "Component.h"
#include "Property.h"

class GameObject;
class Shader;
class Texture;

class SpriteComponent : public Component
{
public:
	/**
	@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	@param	�R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
	*/
    SpriteComponent(GameObject* argOwner, int argDrawOrder = 100);
    ~SpriteComponent();

	/**
	@brief	�`�揈��
	@param	�g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
    virtual void Draw(Shader* shader);

	/**
	@brief	�g�p����e�N�X�`���̐ݒ�
	@param	�g�p����e�N�X�`���̃|�C���^
	*/
    virtual void SetTexture(Texture* argTexture);

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

