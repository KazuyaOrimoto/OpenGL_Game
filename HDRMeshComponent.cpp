#include "HDRMeshComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "Shader.h"
#include "Mesh.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Texture.h"


HDRMeshComponent::HDRMeshComponent(GameObject* _owner, ShaderType _shaderType)
	: MeshComponent(_owner,_shaderType)
{
}

HDRMeshComponent::~HDRMeshComponent()
{
}

void HDRMeshComponent::Draw(Shader * _shader)
{
	_shader->SetFloatUniform("uIntensity", intensity);
	MeshComponent::Draw(_shader);
}
