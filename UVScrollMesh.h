#pragma once
#include "MeshComponent.h"

class GameObject;

class UVScrollMesh :
	public MeshComponent
{
public:
	UVScrollMesh(GameObject* _owner);
	~UVScrollMesh();

	/**
	@brief�@�`�揈��
	@param	�g�p����V�F�[�_�[�N���X�̃|�C���^
	*/
	virtual void Draw(Shader* _shader);
};

