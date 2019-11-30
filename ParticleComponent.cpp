#include "ParticleComponent.h"
#include "Shader.h"
#include "Renderer.h"
#include "GameObject.h"

Matrix4 ParticleComponent::staticBillboardMat;
Vector3 ParticleComponent::staticCameraWorldPos;

ParticleComponent::ParticleComponent(GameObject * _owner)
	:Component(_owner)
	, position(_owner->GetPosition())
	, life(0.0f)
	, alpha(1.0f)
	, isFollowing(true)
{
	RENDERER->AddParticle(this);
}

ParticleComponent::ParticleComponent(GameObject * _owner, const Vector3 & _pos, const Vector3 & _v, float _scale, float _alpha, float _life)
	: Component(_owner)
	, position(_pos + _owner->GetPosition())
	, velocity(_v)
	, scale(_scale)
	, life(_life)
	, alpha(_alpha)
	, nowTime(0.0)
	, blendType(PARTICLE_BLEND_ENUM::PARTICLE_BLEND_ENUM_ALPHA)
	, isFollowing(true)
{
	RENDERER->AddParticle(this);
}

ParticleComponent::~ParticleComponent()
{
}

void ParticleComponent::Update(float _deltaTime)
{
	if (!IsAlive())
	{
		owner->RemoveComponent(this);
	}
	nowTime += _deltaTime;
	velocity = velocity + acceleration;
	position = position + velocity;

	// ŽžŠÔ‚Æ‚Æ‚à‚ÉƒAƒ‹ƒtƒ@”–‚­‚·‚é
	alpha = (life - nowTime) / life;
}

void ParticleComponent::Draw(Shader * shader)
{
	Matrix4 mat, matScale;
	matScale = Matrix4::CreateScale(scale * owner->GetScale());
	if (isFollowing)
	{
		mat = Matrix4::CreateTranslation(position + owner->GetPosition());
	}
	else
	{
		mat = Matrix4::CreateTranslation(position);
	}

	shader->SetMatrixUniform("uWorldTransform", matScale * staticBillboardMat * mat);
	shader->SetFloatUniform("uAlpha", alpha);
	shader->SetVectorUniform("uColor", color);

	RENDERER->SetParticleVertex();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

bool ParticleComponent::IsAlive() const
{
	return nowTime < life;
}

bool ParticleComponent::operator<(const ParticleComponent & rhs) const
{
	float lenThis, lenRhs;
	lenThis = (staticCameraWorldPos - position).LengthSq();
	lenRhs = (staticCameraWorldPos - rhs.position).LengthSq();
	return lenThis < lenRhs;
}

bool ParticleComponent::operator>(const ParticleComponent & rhs) const
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
