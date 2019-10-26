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

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 異方性フィルタリングが使えるかどうか
	if (GLEW_EXT_texture_filter_anisotropic)
	{
		// 最大の異方性を示す値を取得する
		GLfloat largest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
		// 異方性フィルタリングを有効にする
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
	}

	return true;
}

/**
@brief	ロードしたテクスチャの解放
*/
void Texture::Unload()
{
	glDeleteTextures(1,&textureID);
}

void Texture::CreateFromSurface(SDL_Surface * surface)
{
	width = surface->w;
	height = surface->h;

	// Generate a GL texture
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA,
		GL_UNSIGNED_BYTE, surface->pixels);

	// Use linear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

/**
@brief	レンダリング用のテクスチャを作成
@param	テクスチャの横幅
@param	テクスチャの縦幅
@param	ピクセルデータのフォーマット
*/
void Texture::CreateForRendering(int _width, int _height, unsigned int _format)
{
	width = _width;
	height = _height;
	// テクスチャIDの作成
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// 画像の幅と高さを設定（初期データは指定しない）
	glTexImage2D(GL_TEXTURE_2D, 0, _format, width, height, 0, GL_RGB,
		GL_FLOAT, nullptr);

	// レンダリング先のテクスチャには最近傍フィルタリングのみを使う
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

/**
@brief	テクスチャをアクティブにする
*/
void Texture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D,textureID);
}
