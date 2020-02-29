//=============================================================================
//	@file	HDRMeshComponent.cpp
//	@brief	HDR用のメッシュコンポーネント
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#include "HDRMeshComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "Shader.h"
#include "Mesh.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Texture.h"

HDRMeshComponent::HDRMeshComponent(GameObject* _owner)
	: MeshComponent(_owner)
{
}

HDRMeshComponent::~HDRMeshComponent()
{
}

void HDRMeshComponent::Draw(Shader * _shader)
{
	_shader->SetFloatUniform("uIntensity", intensity);
	_shader->SetVectorUniform("uHDRColor", hdrColor);
	MeshComponent::Draw(_shader);
}
