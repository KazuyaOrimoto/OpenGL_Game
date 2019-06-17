#pragma once

#include <string>

class Texture
{
public:
    Texture();
    ~Texture();
	/**
	@brief	テクスチャのロード
	@param	テクスチャのファイル名
	@return	true : 成功 , false : 失敗
	*/
	bool Load(const std::string& fileName);
	/**
	@brief	ロードしたテクスチャの解放
	*/
	void Unload();

	/**
	@brief	テクスチャをアクティブにする
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

