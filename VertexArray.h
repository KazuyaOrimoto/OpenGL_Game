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
	unsigned int numVerts;
	unsigned int numIndices;
	unsigned int vertexBuffer;
	unsigned int indexBuffer;
	unsigned int vertexArray;
};

