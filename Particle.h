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
	void Draw(class Shader* shader);                                         // �̂��̎��Ƃ� virtual��
	void Update(float deltaTime);                                            // �̂��̎��Ƃ� virtual��

	// �Q�b�^�[�n
	const Vector3&       GetPosition()  { return mPosition; }
	const Vector3&       GetVelocity()  { return mVelocity; }
	int                  GetTextureID() { return mTextureID; }
	PARTICLE_ENUM        GetBlendType() { return mBlendType; }

	// �Z�b�^�[�n
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

	// �J���������ł̃\�[�g�p
	bool                 operator < (const Particle& rhs) const;
	bool                 operator > (const Particle& rhs) const;

private:
	Vector3              mPosition             ; // �ʒu
	Vector3              mVelocity             ; // ���x
	Vector3              mAcceleration         ; // �����x
	Vector3              mColor                ; // �F
	float                mAlpha                ; // ��
	float                mLife                 ; // ��������
	float                mNowTime              ; // ���݂̎���
	float                mScale                ; // �X�P�[��
	int                  mTextureID            ; // �e�N�X�`��ID
	PARTICLE_ENUM        mBlendType            ; // �u�����h�^�C�v

	// ���L�X�^�e�B�b�N�����o
	static Matrix4       mStaticBillboardMat   ; // �r���{�[�h�s��
	static Vector3       mStaticCameraWorldPos ; // �J�����̃��[���h���W

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
//	// �Z�b�^�[
//	void   SetMaxEmitParFrame(size_t maxEmit)    { mMaxEmitParFrame = maxEmit  ; }
//	void   SetMaxSize(float maxSize)             { mMaxSize         = maxSize  ; }
//	void   SetMaxLifeTime(float lifeTime)        { mMaxLife         = lifeTime ; }
//	void   SetFirstVelocity(const Vector3 v)     { mFirstVelocity   = v        ; }
//	void   SetAccelaration(const Vector3 accel)  { mAcceleration    = accel    ; }
//
//	// �Q�b�^�[
//	size_t GetActiveParticleNum()                { return mParticles.size(); }
//
//private:
//	size_t mTextureIndex;                      // �e�N�X�`���C���f�b�N�X
//	std::list <class Particle> mParticles;           // �p�[�e�B�N���̃��X�g
//
//	Vector3 mFirstVelocity;                    // �����x�N�g��
//	Vector3 mAcceleration;                     // �p�[�e�B�N�������x
//	float   mMaxSize;                          // �p�[�e�B�N���ő�T�C�Y
//	float   mMaxLife;                          // �p�[�e�B�N���ő����
//	float   mEmitterLife;                      // ���̃G�~�b�^�[�̐�������
//	size_t  mMaxEmitParFrame;                  // 1�t���[��������̃p�[�e�B�N���ő吶����
//	
//};
