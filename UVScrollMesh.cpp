#include "UVScrollMesh.h"
#include "GameObject.h"
#include "Game.h"
#include "Shader.h"
#include "Mesh.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Texture.h"


UVScrollMesh::UVScrollMesh(GameObject* _owner)
	:MeshComponent(_owner)
{
}


UVScrollMesh::~UVScrollMesh()
{
}

void UVScrollMesh::Draw(Shader * _shader)
{
	_shader->SetFloatUniform("uTime",
		static_cast<float>(SDL_GetTicks() / 100));
	MeshComponent::Draw(_shader);
}

