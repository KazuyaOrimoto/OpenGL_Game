#pragma once
#include "MeshComponent.h"

class GameObject;

class UVScrollMesh :
	public MeshComponent
{
public:
	UVScrollMesh(GameObject* _owner);
	~UVScrollMesh();

	/**
	@brief　描画処理
	@param	使用するシェーダークラスのポインタ
	*/
	virtual void Draw(Shader* _shader);
};

