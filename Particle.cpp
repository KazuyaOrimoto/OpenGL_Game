#include "Particle.h"
#include "Component.h"
#include "GameObject.h"
#include "Shader.h"

Matrix4 Particle::mStaticBillboardMat;   // ビルボード行列
Vector3 Particle::mStaticCameraWorldPos; // カメラワールド位置

Particle::Particle()
	: mLife(0.0f)
	, mAlpha(1.0f)
{
}

Particle::Particle(const Vector3 & pos, const Vector3 & v, float scale, float alpha, float life)
	:mPosition(pos)
	,mVelocity(v)
	,mScale(scale)
	,mLife(life)
	,mAlpha(alpha)
	,mNowTime(0.0)
	,mBlendType(PARTICLE_BLEND_ENUM_ALPHA)
{
}

Particle::~Particle()
{
}

void Particle::Draw(Shader* shader)
{
	Matrix4 mat,scale,billboard;
	scale = Matrix4::CreateScale(mScale);
	mat   = Matrix4::CreateTranslation(mPosition);

	shader->SetMatrixUniform("uWorldTransform", scale * mStaticBillboardMat * mat);
	shader->SetFloatUniform("uAlpha", mAlpha);
	shader->SetVectorUniform("uColor", mColor);

	RENDERER->SetParticleVertex();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Particle::Update(float deltaTime)
{
	mNowTime += deltaTime;
	mVelocity = mVelocity + mAcceleration;
	mPosition = mPosition + mVelocity;
	
	// 時間とともにアルファ薄くする
	mAlpha = (mLife - mNowTime) / mLife;

}

bool Particle::IsAlive() const
{
	return mNowTime < mLife;
}

// カメラ距離での大小関係 < 
bool Particle::operator<(const Particle & rhs) const
{
	float lenThis, lenRhs;
	lenThis = (mStaticCameraWorldPos - mPosition).LengthSq();
	lenRhs  = (mStaticCameraWorldPos - rhs.mPosition).LengthSq();
	return lenThis < lenRhs;
}

// カメラ距離での大小関係 > 
bool Particle::operator>(const Particle & rhs) const
{
	float lenThis, lenRhs;
	lenThis = (mStaticCameraWorldPos - mPosition).LengthSq();
	lenRhs  = (mStaticCameraWorldPos - rhs.mPosition).LengthSq();
	return lenThis > lenRhs;
}
