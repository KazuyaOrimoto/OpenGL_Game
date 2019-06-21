#pragma once

#include "Component.h"

class GameObject;
class Shader;
class Mesh;

class MeshComponent : public Component
{
public:
	/**
	@param	アタッチするゲームオブジェクトのポインタ
	*/
    MeshComponent(GameObject* owner);
    ~MeshComponent();

	/**
	@brief　描画処理
	@param	使用するシェーダークラスのポインタ
	*/
    virtual void Draw(Shader* shader);

	/**
	@brief　メッシュコンポーネントが使うMeshの設定
	@param	設定するMeshクラスのポインタ
	*/
    virtual void SetMesh(Mesh* argMesh) { mMesh = argMesh; }

	/**
	@brief　メッシュコンポーネントが使うTextureインデックスの設定
	@param	設定するTextureインデックスの数
	*/
    void SetTextureIndex(size_t index) { mTextureIndex = index; }

protected:

	//クラスのポインタ

    Mesh* mMesh;
    size_t mTextureIndex;
};

