//=============================================================================
//	@file	HDRMeshComponent.h
//	@brief	HDR用のメッシュコンポーネント
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#pragma once
#include "MeshComponent.h"

class GameObject;
class Shader;
class Mesh;

class HDRMeshComponent :
	public MeshComponent
{
public:
	HDRMeshComponent(GameObject* _owner);
	~HDRMeshComponent();

	/**
	@brief　描画処理
	@param	使用するシェーダークラスのポインタ
	*/
	virtual void Draw(Shader* _shader) override;

	void SetIntensity(float _intensity) { intensity = _intensity; }

	float GetIntensity()const { return intensity; }

	const Vector3& GetHDRColor() const { return hdrColor; }
	void SetHDRColor(const Vector3& _color) { hdrColor = _color; }

private:
	float intensity;
	Vector3 hdrColor;
};
