#pragma once

#include <string>

class Texture
{
public:
    Texture();
    ~Texture();
	/**
	@brief	�e�N�X�`���̃��[�h
	@param	�e�N�X�`���̃t�@�C����
	@return	true : ���� , false : ���s
	*/
	bool Load(const std::string& fileName);
	/**
	@brief	���[�h�����e�N�X�`���̉��
	*/
	void Unload();

	/**
	@brief	�e�N�X�`�����A�N�e�B�u�ɂ���
	*/
	void SetActive();

	// Getter / Setter

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

private:
	unsigned int textureID;

	int width;
	int height;
};

