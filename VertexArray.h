#pragma once
class VertexArray
{
public:
	/**
	@param	���_�o�b�t�@�̔z��̃|�C���^
	@param	���_��
	@param	�C���f�b�N�X�o�b�t�@�̔z��̃|�C���^
	@param	�C���f�b�N�X�̐�
	*/
	VertexArray(const float* argVerts, unsigned int argNumVerts,
		const unsigned int* argIndices, unsigned int argNumIndices);
	~VertexArray();

	/**
	@brief	���_�z����A�N�e�B�u�ɂ���i�`��Ɏg�p�ł���悤�ɂ���j
	*/
	void SetActive();

	unsigned int GetNumIndices() const { return numIndices; }
	unsigned int GetNumVerts() const { return numVerts; }

private:
	//���_�o�b�t�@�ɂ��钸�_�̐�
	unsigned int numVerts;
	//�C���f�N�X�o�b�t�@�ɂ���C���f�b�N�X�̐�
	unsigned int numIndices;
	//���_�o�b�t�@��OpenGL ID
	unsigned int vertexBuffer;
	//�C���f�b�N�X�o�b�t�@��OpenGL ID
	unsigned int indexBuffer;
	//���_�z��I�u�W�F�N�g��OpenGL ID
	unsigned int vertexArray;
};

