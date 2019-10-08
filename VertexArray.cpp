#include "VertexArray.h"
#include <glew.h>

/**
@param	頂点バッファの配列のポインタ
@param	頂点数
@param	インデックスバッファの配列のポインタ
@param	インデックスの数
*/
VertexArray::VertexArray(const float* _verts, unsigned int _numVerts,
	const unsigned int* _indices, unsigned int _numIndices)
	:numVerts(_numVerts)
	,numIndices(_numIndices)
{
	// 頂点配列の作成
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// 頂点バッファの作成
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _numVerts * 8 * sizeof(float), _verts, GL_STATIC_DRAW);

	// インデクスバッファの作成
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _numIndices * sizeof(unsigned int), _indices, GL_STATIC_DRAW);

	//最初の頂点属性を有効に（位置座標）
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,						//頂点属性インデックス（位置座標）
		3,						//要素の数
		GL_FLOAT,				//要素の型
		GL_FALSE,				//（GL_FLOATには使わない）
		sizeof(float) * 8,		//各頂点のサイズ
		0						//頂点データの開始位置からこの属性までのオフセット
	);
	//第2の頂点属性を有効に（法線ベクトル）
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,						//頂点属性インデックス（法線ベクトル）
		3,						//要素の数
		GL_FLOAT,				//要素の型
		GL_FALSE,				//（GL_FLOATには使わない）
		sizeof(float) * 8,		//各頂点のサイズ
		reinterpret_cast<void*>(sizeof(float) * 3));	//オフセットポインタ
    //第3の頂点属性を有効に（テクスチャ座標）
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2,						//頂点属性インデックス（テクスチャ座標）
        2,						//要素の数（UVは2個）
        GL_FLOAT,				//要素の型
        GL_FALSE,				//（GL_FLOATには使わない）
        sizeof(float) * 8,		//各頂点のサイズ
        reinterpret_cast<void*>(sizeof(float) * 6));	//オフセットポインタ
}


VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteVertexArrays(1, &vertexArray);
}

/**
@brief	頂点配列をアクティブにする
*/
void VertexArray::SetActive()
{
	glBindVertexArray(vertexArray);
}
