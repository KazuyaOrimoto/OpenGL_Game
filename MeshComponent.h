#pragma once

#include "Component.h"

class GameObject;
class Shader;
class Mesh;

enum ShaderType
{
	DEFAULT,
	WALL,
	UV_SCROLL
};

class MeshComponent : public Component
{
public:
	/**
	@param	アタッチするゲームオブジェクトのポインタ
	*/
    MeshComponent(GameObject* _owner, ShaderType _shaderType = DEFAULT);
    ~MeshComponent();

	/**
	@brief　描画処理
	@param	使用するシェーダークラスのポインタ
	*/
    virtual void Draw(Shader* _shader);

	/**
	@brief　メッシュコンポーネントが使うMeshの設定
	@param	設定するMeshクラスのポインタ
	*/
    virtual void SetMesh(Mesh* _mesh) { mMesh = _mesh; }

	virtual Mesh* GetMesh() { return mMesh; }

    ShaderType GetShaderName() { return shaderName; }
	void SetShaderName(ShaderType _shaderName) { shaderName = _shaderName; }

	/**
	@brief　メッシュコンポーネントが使うTextureインデックスの設定
	@param	設定するTextureインデックスの数
	*/
    void SetTextureIndex(size_t _index) { mTextureIndex = _index; }

	/**
	@brief　描画をするかどうかを設定
	@param	true : 描画する , false : 描画しない
	*/
	void SetVisible(bool _visible) { visible = _visible; }

	/**
	@brief　描画をするかどうかを取得する
	@return	true : 描画する , false : 描画しない
	*/
	bool GetVisible() const { return visible; }

protected:

	//クラスのポインタ

    Mesh* mMesh;
    size_t mTextureIndex;

    ShaderType shaderName;

	//描画をするかどうか
	bool visible;
};

