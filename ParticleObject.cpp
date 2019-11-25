#include "ParticleObject.h"
#include "Renderer.h"
#include "Shader.h"

Matrix4 ParticleObject::staticBillboardMat;   // ビルボード行列
Vector3 ParticleObject::staticCameraWorldPos; // カメラワールド位置

ParticleObject::ParticleObject()
	: life(0.0f)
	, alpha(1.0f)
{
}

ParticleObject::ParticleObject(const Vector3 & _pos, const Vector3 & _v, float _scale, float _alpha, float _life)
	: GameObject()
	, velocity(_v)
	, life(_life)
	, alpha(_alpha)
	, nowTime(0.0)
	, blendType(PARTICLE_BLEND_ENUM_ALPHA)
{
	position = _pos;
	scale = _scale;
}


ParticleObject::~ParticleObject()
{
}

void ParticleObject::UpdateGameObject(float _deltaTime)
{
	nowTime += _deltaTime;
	velocity = velocity + acceleration;
	position = position + velocity;

	// 時間とともにアルファ薄くする
	alpha = (life - nowTime) / life;
}

void ParticleObject::Draw(Shader * shader)
{
	Matrix4 mat, matScale;
	matScale = Matrix4::CreateScale(scale);
	mat = Matrix4::CreateTranslation(position);

	shader->SetMatrixUniform("uWorldTransform", matScale * staticBillboardMat * mat);
	shader->SetFloatUniform("uAlpha", alpha);
	shader->SetVectorUniform("uColor", color);

	RENDERER->SetParticleVertex();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

bool ParticleObject::IsAlive() const
{
	return nowTime < life;
}

bool ParticleObject::operator<(const ParticleObject & rhs) const
{
	float lenThis, lenRhs;
	lenThis = (staticCameraWorldPos - position).LengthSq();
	lenRhs = (staticCameraWorldPos - rhs.position).LengthSq();
	return lenThis < lenRhs;
}

bool ParticleObject::operator>(const ParticleObject & rhs) const
{
	float lenThis, lenRhs;
	lenThis = (staticCameraWorldPos - position).LengthSq();
	lenRhs = (staticCameraWorldPos - rhs.position).LengthSq();
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
