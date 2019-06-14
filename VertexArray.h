#pragma once
class VertexArray
{
public:
	VertexArray(const float* argVerts, unsigned int argNumVerts,
		const unsigned int* argIndices, unsigned int argNumIndices);
	~VertexArray();

	void SetActive();

	unsigned int GetNumIndices() const { return numIndices; }
	unsigned int GetNumVerts() const { return numVerts; }

private:
	//頂点バッファにある頂点の数
	unsigned int numVerts;
	//インデクスバッファにあるインデックスの数
	unsigned int numIndices;
	//頂点バッファのOpenGL ID
	unsigned int vertexBuffer;
	//インデックスバッファのOpenGL ID
	unsigned int indexBuffer;
	//頂点配列オブジェクトのOpenGL ID
	unsigned int vertexArray;
};

