#pragma once

#include <vector>
#include <string>
#include "Math.h"

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
    bool Load(const std::string& _fileName, Renderer* _renderer);

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
    Texture* GetTexture(size_t _index);

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

	std::vector<Vector3> GetVerts() {return verts;}

private:
    //このメッシュに使うテクスチャのポインタの可変長コンテナ
    std::vector<Texture*> textures;
	//このメッシュに使う頂点データ
	std::vector<Vector3> verts;

	//クラスのポインタ

    VertexArray* vertexArray;

    //このメッシュに使うシェーダーの名前
    std::string shaderName;
    //オブジェクト空間での境界球の半径
    float radius;
    //鏡面反射成分の大きさ
    float specPower;
};