#pragma once

#include "Component.h"

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
    SpriteComponent(GameObject* _owner, int _drawOrder = 100);
    ~SpriteComponent();

	/**
	@brief	描画処理
	@param	使用するシェーダークラスのポインタ
	*/
    virtual void Draw(Shader* _shader);

	/**
	@brief	使用するテクスチャの設定
	@param	使用するテクスチャのポインタ
	*/
    virtual void SetTexture(Texture* _texture);

	/**
	@brief	テクスチャの横幅を取得する
	@return テクスチャの横幅
	*/
    int GetTexWidth() const { return textureWidth; }

	/**
	@brief	テクスチャの縦幅を取得する
	@return テクスチャの縦幅
	*/
    int GetTexHeight() const { return textureHeight; }

	/**
	@brief	DrawOrderを取得する
	@return DrawOrder（数値が少ないほど早く更新される）
	*/
	int GetDrawOrder() { return drawOrder; }

protected:

	//クラスのポインタ

    Texture* texture;

	//描画される順番（数値が少ないほど早く更新される）
    int drawOrder;
	//テクスチャの横幅
    int textureWidth;
	//テクスチャの縦幅
    int textureHeight;
};

