#pragma once

#include "Component.h"

class GameObject;
class Shader;
class Mesh;

class MeshComponent : public Component
{
public:
	/**
	@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	*/
    MeshComponent(GameObject* owner);
    ~MeshComponent();

	/**
	@brief�@�`�揈��
	@param	�g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
    virtual void Draw(Shader* shader);

	/**
	@brief�@���b�V���R���|�[�l���g���g��Mesh�̐ݒ�
	@param	�ݒ肷��Mesh�N���X�̃|�C���^
	*/
    virtual void SetMesh(Mesh* argMesh) { mMesh = argMesh; }

	/**
	@brief�@���b�V���R���|�[�l���g���g��Texture�C���f�b�N�X�̐ݒ�
	@param	�ݒ肷��Texture�C���f�b�N�X�̐�
	*/
    void SetTextureIndex(size_t index) { mTextureIndex = index; }

protected:

	//�N���X�̃|�C���^

    Mesh* mMesh;
    size_t mTextureIndex;
};

