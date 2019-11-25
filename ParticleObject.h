#pragma once
#include "GameObject.h"
#include "Math.h"


class ParticleObject :
	public GameObject
{
public:
	typedef enum PARTICLE_BLEND_ENUM
	{
		PARTICLE_BLEND_ENUM_ALPHA,
		PARTICLE_BLEND_ENUM_ADD,
		PARTICLE_BLEND_ENUM_MULT
	}PARTICLE_ENUM;
	ParticleObject();
	ParticleObject(const Vector3& pos, const Vector3& v, float scale, float alpha, float life);
	~ParticleObject();

	/**
	@brief	ゲームオブジェクトのアップデート
	@param	最後のフレームを完了するのに要した時間
	*/
	virtual void UpdateGameObject(float _deltaTime) override;

	void Draw(class Shader* shader);// のちの授業で virtualに

private:
	Vector3              velocity; // 速度
	Vector3              acceleration; // 加速度
	Vector3              color; // 色
	float                alpha; // α
	float                life; // 生存時間
	float                nowTime; // 現在の時間
	int                  textureID; // テクスチャID
	PARTICLE_ENUM        blendType; // ブレンドタイプ

	// 共有スタティックメンバ
	static Matrix4       staticBillboardMat; // ビルボード行列
	static Vector3       staticCameraWorldPos; // カメラのワールド座標

public:
	const Vector3&       GetVelocity() { return velocity; }
	int                  GetTextureID() { return textureID; }
	PARTICLE_ENUM        GetBlendType() { return blendType; }

	void                 SetVelocity(const Vector3& v) { velocity = v; }
	void                 SetColor(const Vector3& c) { color = c; }
	void                 SetTextureID(int texID) { textureID = texID; }
	void                 SetAlpha(float alpha) { alpha = alpha; }
	void                 SetBillboardMat(const Matrix4& mat)
	{
		staticBillboardMat = mat;
	}
	void                 SetBlendMode(PARTICLE_ENUM blendType)
	{
		blendType = blendType;
	}
	bool                 IsAlive() const;

	// カメラ距離でのソート用
	bool                 operator < (const ParticleObject& rhs) const;
	bool                 operator > (const ParticleObject& rhs) const;

};

Matrix4 GetBillboardMatrix();

