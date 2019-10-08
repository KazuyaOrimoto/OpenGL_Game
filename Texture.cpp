#include "Texture.h"
#include <SOIL.h>
#include <glew.h>
#include <SDL.h>

Texture::Texture()
	:textureID(0)
	,width(0)
	,height(0)
{
}


Texture::~Texture()
{
}

/**
@brief	テクスチャのロード
@param	テクスチャのファイル名
@return	true : 成功 , false : 失敗
*/
bool Texture::Load(const std::string& _fileName)
{
	int channels = 0;

	unsigned char* image = SOIL_load_image(_fileName.c_str(),
											&width,&height,&channels,SOIL_LOAD_AUTO);

	if (image == nullptr)
	{
		SDL_Log("SOIL failed to load image %s: %s", _fileName.c_str(), SOIL_last_result());
		return false;
	}

	int format = GL_RGB;
	if (channels == 4)
	{
		format = GL_RGBA;
	}

	glGenTextures(1,&textureID);
	glBindTexture(GL_TEXTURE_2D,textureID);

	glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE,image);

	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

/**
@brief	ロードしたテクスチャの解放
*/
void Texture::Unload()
{
	glDeleteTextures(1,&textureID);
}

/**
@brief	テクスチャをアクティブにする
*/
void Texture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D,textureID);
}
