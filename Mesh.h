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
	@brief  メッシュデータの読み込み
	@param	ロードしたいメッシュのファイル名
	@param	Rendererクラスのポインタ
	@return true : 成功 , false : 失敗
	*/
    bool Load(const std::string& argFileName, Renderer* argRenderer);

	/**
	@brief  ロードしたメッシュデータの解放
	*/
    void Unload();
	
	/**
	@brief	メッシュの頂点配列を取得する
	@return	VertexArray型のポインタ
	*/
    VertexArray* GetVertexArray() { return vertexArray; }

	/**
	@brief	インデクスからメッシュに使っているテクスチャを取得する
	@param	テクスチャのインデックス
	@return Textureクラスのポインタ
	*/
    Texture* GetTexture(size_t argIndex);

	/**
	@brief	インデクスからメッシュに使っているテクスチャを取得する
	@param	テクスチャのインデックス
	@return Textureクラスのポインタ
	*/
    const std::string& GetShaderName() const { return shaderName; }

	/**
	@brief	オブジェクト空間で境界球の半径を取得する
	@return radius（半径）
	*/
    float GetRadius() const { return radius; }

	/**
	@brief	鏡面反射成分の大きさを取得する
	@return specPower（鏡面反射成分）
	*/
    float GetSpecPower() const { return specPower; }

private:
    //このメッシュに使うテクスチャのポインタの可変長コンテナ
    std::vector<Texture*> textures;

	//クラスのポインタ

    VertexArray* vertexArray;

    //このメッシュに使うシェーダーの名前
    std::string shaderName;
    //オブジェクト空間での境界球の半径
    float radius;
    //鏡面反射成分の大きさ
    float specPower;
};