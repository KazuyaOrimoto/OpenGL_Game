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

	class Shader*                     mShader;           // シェーダー
	std::vector<class Particle*>      mParticles;        // パーティクル配列
	std::vector<class Particle*>      mPendingParticles; // ペンディングアクター配列

	Matrix4                           mViewMat;          // ビュー行列
	Matrix4                           mProjectionMat;    // プロジェクション行列
	Matrix4                           mBillboardMat;     // ビルボード行列

};