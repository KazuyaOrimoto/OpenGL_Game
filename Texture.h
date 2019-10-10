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
	bool Load(const std::string& _fileName);
	/**
	@brief	ロードしたテクスチャの解放
	*/
	void Unload();

	/**
	@brief	テクスチャをアクティブにする
	*/
	void SetActive();

	/**
	@brief	テクスチャの横幅を取得する
	@return 横幅
	*/
	int GetWidth() const { return width; }

	/**
	@brief	テクスチャの縦幅を取得する
	@return 縦幅
	*/
	int GetHeight() const { return height; }

private:
	unsigned int textureID;

	//テクスチャの横幅
	int width;
	//テクスチャの縦幅
	int height;
};

