#pragma once
#include "game.h"
#include "Renderer.h"
#include "Shader.h"
#include "Particle.h"
#include <vector>
#include <map>

class ParticleManager
{
public:
	ParticleManager();
	~ParticleManager();
	void Draw();
	void SetParticle(class Particle* particle);
	void Update(float deltaTime);

private:

	void ChangeBlendMode(Particle::PARTICLE_BLEND_ENUM blendType);
	void ChangeTexture(int changeTextureID);
	Vector3 CalcCameraPos();

	class Shader*                     mShader;           // �V�F�[�_�[
	std::vector<class Particle*>      mParticles;        // �p�[�e�B�N���z��
	std::vector<class Particle*>      mPendingParticles; // �y���f�B���O�A�N�^�[�z��

	Matrix4                           mViewMat;          // �r���[�s��
	Matrix4                           mProjectionMat;    // �v���W�F�N�V�����s��
	Matrix4                           mBillboardMat;     // �r���{�[�h�s��

};