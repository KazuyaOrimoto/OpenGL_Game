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

	// Getter / Setter

    VertexArray* GetVertexArray() { return vertexArray; }
    Texture* GetTexture(size_t argIndex);
    const std::string& GetShaderName() const { return shaderName; }
    float GetRadius() const { return radius; }
    float GetSpecPower() const { return specPower; }

private:
    //このメッシュに使うテクスチャのポインタの可変長コンテナ
    std::vector<Texture*> textures;

	//クラスのポインタ

    VertexArray* vertexArray;

    //このメッシュに使うシェーダーの名前
    std::string shaderName;
    //オブジェクト空間での境界球の半径を記録
    float radius;
    //鏡面反射成分の大きさ
    float specPower;
};