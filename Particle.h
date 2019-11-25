#pragma once
#include "Game.h"
#include "Renderer.h"
#include "Component.h"
#include <list>

class Particle 
{

public:
	typedef enum PARTICLE_BLEND_ENUM
	{
		PARTICLE_BLEND_ENUM_ALPHA,
		PARTICLE_BLEND_ENUM_ADD,
		PARTICLE_BLEND_ENUM_MULT
	}PARTICLE_ENUM;

	Particle();
	Particle(const Vector3& pos, const Vector3& v, float scale, float alpha, float life);
	~Particle();
	void Draw(class Shader* shader);                                         // のちの授業で virtualに
	void Update(float deltaTime);                                            // のちの授業で virtualに

	// ゲッター系
	const Vector3&       GetPosition()  { return mPosition; }
	const Vector3&       GetVelocity()  { return mVelocity; }
	int                  GetTextureID() { return mTextureID; }
	PARTICLE_ENUM        GetBlendType() { return mBlendType; }

	// セッター系
	void                 SetPosition(const Vector3& pos) { mPosition  = pos   ; }
	void                 SetVelocity(const Vector3& v)   { mPosition  = v     ; }
	void                 SetColor(const Vector3& c)      { mColor     = c     ; }
	void                 SetTextureID(int texID)         { mTextureID = texID ; }
	void                 SetScale(float scale)           { mScale     = scale ; }
	void                 SetAlpha(float alpha)           { mAlpha     = alpha ; }
	void                 SetBillboardMat(const Matrix4& mat)
                                                         { mStaticBillboardMat = mat; }
	void                 SetBlendMode(PARTICLE_ENUM blendType)
	                                                     { mBlendType = blendType; }
	bool                 IsAlive() const; 

	// カメラ距離でのソート用
	bool                 operator < (const Particle& rhs) const;
	bool                 operator > (const Particle& rhs) const;

private:
	Vector3              mPosition             ; // 位置
	Vector3              mVelocity             ; // 速度
	Vector3              mAcceleration         ; // 加速度
	Vector3              mColor                ; // 色
	float                mAlpha                ; // α
	float                mLife                 ; // 生存時間
	float                mNowTime              ; // 現在の時間
	float                mScale                ; // スケール
	int                  mTextureID            ; // テクスチャID
	PARTICLE_ENUM        mBlendType            ; // ブレンドタイプ

	// 共有スタティックメンバ
	static Matrix4       mStaticBillboardMat   ; // ビルボード行列
	static Vector3       mStaticCameraWorldPos ; // カメラのワールド座標

	friend class ParticleManager;
};



//class ParticleEmitter : public Component
//{
//public:
//	ParticleEmitter(class Actor* owner);
//	~ParticleEmitter();
//
//	void Draw(class Shader* shader);
//	void SetTextureIndex(size_t index);
//	void Update(float deltaTime) override;
//
//	// セッター
//	void   SetMaxEmitParFrame(size_t maxEmit)    { mMaxEmitParFrame = maxEmit  ; }
//	void   SetMaxSize(float maxSize)             { mMaxSize         = maxSize  ; }
//	void   SetMaxLifeTime(float lifeTime)        { mMaxLife         = lifeTime ; }
//	void   SetFirstVelocity(const Vector3 v)     { mFirstVelocity   = v        ; }
//	void   SetAccelaration(const Vector3 accel)  { mAcceleration    = accel    ; }
//
//	// ゲッター
//	size_t GetActiveParticleNum()                { return mParticles.size(); }
//
//private:
//	size_t mTextureIndex;                      // テクスチャインデックス
//	std::list <class Particle> mParticles;           // パーティクルのリスト
//
//	Vector3 mFirstVelocity;                    // 初速ベクトル
//	Vector3 mAcceleration;                     // パーティクル加速度
//	float   mMaxSize;                          // パーティクル最大サイズ
//	float   mMaxLife;                          // パーティクル最大寿命
//	float   mEmitterLife;                      // このエミッターの生存時間
//	size_t  mMaxEmitParFrame;                  // 1フレームあたりのパーティクル最大生成量
//	
//};
