#pragma once

#include <vector>
#include <string>

class Renderer;
class VertexArray;
class Texture;

class Mesh
{
public:
    Mesh();
    ~Mesh();
	/**
	@brief  ���b�V���f�[�^�̓ǂݍ���
	@param	���[�h���������b�V���̃t�@�C����
	@param	Renderer�N���X�̃|�C���^
	@return true : ���� , false : ���s
	*/
    bool Load(const std::string& argFileName, Renderer* argRenderer);

	/**
	@brief  ���[�h�������b�V���f�[�^�̉��
	*/
    void Unload();

	// Getter / Setter

    VertexArray* GetVertexArray() { return vertexArray; }
    Texture* GetTexture(size_t argIndex);
    const std::string& GetShaderName() const { return shaderName; }
    float GetRadius() const { return radius; }
    float GetSpecPower() const { return specPower; }

private:
    //���̃��b�V���Ɏg���e�N�X�`���̃|�C���^�̉ϒ��R���e�i
    std::vector<Texture*> textures;

	//�N���X�̃|�C���^

    VertexArray* vertexArray;

    //���̃��b�V���Ɏg���V�F�[�_�[�̖��O
    std::string shaderName;
    //�I�u�W�F�N�g��Ԃł̋��E���̔��a���L�^
    float radius;
    //���ʔ��ː����̑傫��
    float specPower;
};