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
	@brief	�Q�[���I�u�W�F�N�g�̃A�b�v�f�[�g
	@param	�Ō�̃t���[������������̂ɗv��������
	*/
	virtual void UpdateGameObject(float _deltaTime) override;

	void Draw(class Shader* shader);// �̂��̎��Ƃ� virtual��

private:
	Vector3              velocity; // ���x
	Vector3              acceleration; // �����x
	Vector3              color; // �F
	float                alpha; // ��
	float                life; // ��������
	float                nowTime; // ���݂̎���
	int                  textureID; // �e�N�X�`��ID
	PARTICLE_ENUM        blendType; // �u�����h�^�C�v

	// ���L�X�^�e�B�b�N�����o
	static Matrix4       staticBillboardMat; // �r���{�[�h�s��
	static Vector3       staticCameraWorldPos; // �J�����̃��[���h���W

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

	// �J���������ł̃\�[�g�p
	bool                 operator < (const ParticleObject& rhs) const;
	bool                 operator > (const ParticleObject& rhs) const;

};

Matrix4 GetBillboardMatrix();

