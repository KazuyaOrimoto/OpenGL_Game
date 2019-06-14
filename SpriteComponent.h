#pragma once

#include "Component.h"
#include "Property.h"

class GameObject;
class Shader;
class Texture;

class SpriteComponent : public Component
{
public:
	/**
	@param	アタッチするゲームオブジェクトのポインタ
	@param	コンポーネントの更新順番（数値が小さいほど早く更新される）
	*/
    SpriteComponent(GameObject* argOwner, int argDrawOrder = 100);
    ~SpriteComponent();

	/**
	@brief	描画処理
	@param	使用するシェーダークラスのポインタ
	*/
    virtual void Draw(Shader* shader);

	/**
	@brief	使用するテクスチャの設定
	@param	使用するテクスチャのポインタ
	*/
    virtual void SetTexture(Texture* argTexture);

    int GetTexWidth() const { return textureWidth; }
    int GetTexHeight() const { return textureHeight; }

	cpp_module::ReadOnlyProperty<int> readOnlyDrawOrder;
	cpp_module::ReadOnlyProperty<int> readOnlyTextureWidth;
	cpp_module::ReadOnlyProperty<int> readOnlyTextureHeight;
protected:
    Texture* texture;
    int drawOrder;
    int textureWidth;
    int textureHeight;
};

