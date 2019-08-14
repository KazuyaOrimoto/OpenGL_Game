#pragma once

#include "Component.h"

class GameObject;
class Shader;
class Mesh;

enum ShaderType
{
	DEFAULT,
	WALL
};

class MeshComponent : public Component
{
public:
	/**
	@param	�A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
	*/
    MeshComponent(GameObject* owner, ShaderType argShaderType = DEFAULT);
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

	virtual Mesh* GetMesh() { return mMesh; }

    ShaderType GetShaderName() { return shaderName; }
	void SetShaderName(ShaderType argShaderName) { shaderName = argShaderName; }

	/**
	@brief�@���b�V���R���|�[�l���g���g��Texture�C���f�b�N�X�̐ݒ�
	@param	�ݒ肷��Texture�C���f�b�N�X�̐�
	*/
    void SetTextureIndex(size_t index) { mTextureIndex = index; }

	/**
	@brief�@�`������邩�ǂ�����ݒ�
	@param	true : �`�悷�� , false : �`�悵�Ȃ�
	*/
	void SetVisible(bool argVisible) { visible = argVisible; }

	/**
	@brief�@�`������邩�ǂ������擾����
	@return	true : �`�悷�� , false : �`�悵�Ȃ�
	*/
	bool GetVisible() const { return visible; }

protected:

	//�N���X�̃|�C���^

    Mesh* mMesh;
    size_t mTextureIndex;

    ShaderType shaderName;

	//�`������邩�ǂ���
	bool visible;
};

