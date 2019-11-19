#include "Particle.h"
#include "Component.h"
#include "GameObject.h"
#include "Shader.h"

Matrix4 Particle::mStaticBillboardMat;   // �r���{�[�h�s��
Vector3 Particle::mStaticCameraWorldPos; // �J�������[���h�ʒu

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
	
	// ���ԂƂƂ��ɃA���t�@��������
	mAlpha = (mLife - mNowTime) / mLife;

}

bool Particle::IsAlive() const
{
	return mNowTime < mLife;
}

// �J���������ł̑召�֌W < 
bool Particle::operator<(const Particle & rhs) const
{
	float lenThis, lenRhs;
	lenThis = (mStaticCameraWorldPos - mPosition).LengthSq();
	lenRhs  = (mStaticCameraWorldPos - rhs.mPosition).LengthSq();
	return lenThis < lenRhs;
}

// �J���������ł̑召�֌W > 
bool Particle::operator>(const Particle & rhs) const
{
	float lenThis, lenRhs;
	lenThis = (mStaticCameraWorldPos - mPosition).LengthSq();
	lenRhs  = (mStaticCameraWorldPos - rhs.mPosition).LengthSq();
	return lenThis > lenRhs;
}

Matrix4 GetBillboardMatrix()
{
	Matrix4 ret;
	ret = RENDERER->GetViewMatrix();
	ret.mat[3][0] = ret.mat[3][1] = ret.mat[3][2] = 0.0f;
	ret.Transpose();
	ret.mat[1][1] *= -1;
	ret.mat[2][2] *= -1;

	return Matrix4(ret);
}

